#include "Tree.h"

#include <iostream>
#include <sstream>
#include <algorithm>

#include "model_util.h"
#include "Matrix.h"

Tree_Shadow Node::tree_shadow = {};

Tree::Tree(vec3 const& in_position)
{
    position = in_position;
    generate();
}

Tree::~Tree()
{
    delete root;
}

void Tree::render(Tree_Shader const& shader) const
{
    glBindVertexArray(vao_data.vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, vao_data.material.texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    shader.load_model_matrix(translation_matrix(position.x, position.y, position.z));
    //shader.load_material_properties(*this);

    glDrawElements(GL_TRIANGLES, vao_data.indices_count, GL_UNSIGNED_INT, 0);
}

void Tree::update(float delta_time)
{
    grow();
    recreate_buffer_data();
}

void Tree::generate()
{
    //create trunk
    root = new Node(vec3{0,1,0}, position, 0);
    root->shoot_main(3, 0);

    for(int i = 0; i < 10; i++)
    {
        grow();
    }

    create_buffer_data();
}

float Tree::calc_light_res(int current_time)
{
    // There is more work to be done here, but i think this will work for now.
    //  - Light calculation
    //  - Switch so that light is calculated for buds, not nodes
    //  - ???
    light_res = tree::alpha * root->calc_light_res(current_time);
    return light_res;
}

void Tree::grow()
{
    age++;
    calc_light_res(age);
    root->calc_borchert_honda(light_res, age);
    root->calc_branch_radii();
    root->calc_shedding_branches();
}

void Tree::create_buffer_data()
{
    root->create_buffer_data(data, position);
    vao_data.load_buffer_data(data.vertices, data.normals, data.texture_coords, data.indices);

    vao_data.material.texture_id = model::load_texture("res/tree/oak_texture/Wood_Bark_006_basecolor.jpg");
}

void Tree::recreate_buffer_data()
{
    data.vertices.clear();
    data.normals.clear();
    data.texture_coords.clear();
    data.indices.clear();
    root->create_buffer_data(data, position);
    vao_data.reload_buffer_data(data.vertices, data.normals, data.texture_coords, data.indices);
}

// ==============
// ===| Node |===
// ==============

Node::Node()
{
}

Node::Node(vec3 const& direction, vec3 parent_position, int current_time)
    : direction {direction}, position {parent_position + direction * length}, creation_time {current_time}
{
    tree_shadow.add_node(position);
}

Node::~Node()
{
    //TODO remove node from shadow_map

    delete main_branch;
    delete lateral_branch;
}

float Node::calc_light_res(int current_time)
{
    main_light_res = 0;
    lateral_light_res = 0;

    // calc res from branches
    if (main_branch != nullptr)
    {
        main_light_res = main_branch->calc_light_res(current_time);
    }
    else
    {
        // calc res for apical bud
        float light_exposure {std::max(tree::full_exposure_light - tree_shadow.get_value(position) + tree::a, 0.0f)};
        main_light_res = pow(light_exposure, pow(current_time - creation_time, tree::sigma));
    }
    
    if (lateral_branch != nullptr)
    {
        lateral_light_res += lateral_branch->calc_light_res(current_time);
    }
    else
    {
        // calc res for lateral bud
        float light_exposure {std::max(tree::full_exposure_light - tree_shadow.get_value(position) + tree::a, 0.0f)};
        lateral_light_res = pow(light_exposure, pow(current_time - creation_time, tree::sigma));
    }
    
    return main_light_res + lateral_light_res - tree::BM * pow(radius / tree::default_radius, tree::BE);
}

void Node::calc_borchert_honda(float recieved_light_recources, int current_time)
{
    float vm = recieved_light_recources * ((tree::lambda * main_light_res) / (tree::lambda * main_light_res + (1 - tree::lambda) * lateral_light_res));
    float vl = recieved_light_recources * (((1 - tree::lambda) * lateral_light_res) / (tree::lambda * main_light_res + (1 - tree::lambda) * lateral_light_res));

    if (main_branch != nullptr)
    {
        main_branch->calc_borchert_honda(vm, current_time);
    }
    else
    {
        int nr_new_nodes = static_cast<int>(std::floor(vm));

        shoot_main(nr_new_nodes, current_time);
    }

    if (lateral_branch != nullptr)
    {
        lateral_branch->calc_borchert_honda(vl, current_time);
    }
    else
    {
        int nr_new_nodes = static_cast<int>(std::floor(vl));

        shoot_lateral(nr_new_nodes, current_time);
    }
}

void Node::shoot_main(int nr_new_nodes, int current_time)
{
    if (nr_new_nodes > 0)
    {
        main_branch = new Node(direction, position, current_time);
        main_branch->shoot_main(--nr_new_nodes, current_time);
    }
}

void Node::shoot_lateral(int nr_new_nodes, int current_time)
{
    if (nr_new_nodes > 0)
    {
        vec3 random_vector {(float) rand() / RAND_MAX - 0.5f, (float)rand() / RAND_MAX - 0.5f, (float)rand() / RAND_MAX - 0.5f};
        vec3 shifted_direction {rotation_matrix( 30, random_vector) * direction};
        lateral_branch = new Node(shifted_direction, position, current_time);
        lateral_branch->shoot_main(--nr_new_nodes, current_time);
    }
}

float Node::calc_branch_radii()
{
    float tmp {};
    if (has_lateral_branch())
    {
        tmp += pow(lateral_branch->calc_branch_radii(), 2);
    }
    if (has_main_branch())
    {
        tmp += pow(main_branch->calc_branch_radii(), 2);
    }

    float new_radius = static_cast<float>(sqrt(tmp));
    if (new_radius > radius)
    {
        radius = new_radius;
    }
    return radius;
}

void Node::calc_shedding_branches()
{
    if (has_main_branch())
    {
        if (main_light_res < 0 && main_branch->get_supporting_terminals() < tree::Nmin)
        {
            shed(main_branch);
        } else 
        {
            main_branch->calc_shedding_branches();
        }
    }

    if (has_lateral_branch())
    {
        if (lateral_light_res < 0 && lateral_branch->get_supporting_terminals() < tree::Nmin)
        {
            shed(lateral_branch);
        } else 
        {
            lateral_branch->calc_shedding_branches();
        }
    }
}

void Node::shed(Node* & branch)
{
    delete branch;
    branch = nullptr;
}

std::string Node::to_string() const
{
    std::stringstream output {};

    output << "[lateral: ";
    if (lateral_branch != nullptr)
    {
        output << lateral_branch->to_string();
    }
    output << ", main: ";
    if (main_branch != nullptr)
    {
        output << main_branch->to_string();
    }
    output << "]";
    return output.str();
}

int Node::get_supporting_terminals() const
{
    int sum {0};
    if (has_lateral_branch())
    {
        sum += lateral_branch->get_supporting_terminals();
    }
    if (has_main_branch())
    {
        sum += main_branch->get_supporting_terminals();
    }

    if (sum == 0)
    {
        //is terminal
        return 1;
    }
    return sum;
}

void Node::create_buffer_data(model::Buffer_Data & data, vec3 const& parent_position) const
{

    int nr_points = 10;
    int nr_previously_added_vertices = data.vertices.size() / 3;

    // == Add Vertex and Texture Data ==

    //lower midpoint
    data.vertices.push_back(parent_position.x);
    data.vertices.push_back(parent_position.y);
    data.vertices.push_back(parent_position.z);
    data.texture_coords.push_back(0);
    data.texture_coords.push_back(0);
    data.normals.push_back(0);
    data.normals.push_back(0);
    data.normals.push_back(0);

    //lower surounding points
    float radians_per_point = 360 / nr_points;
    mat4 rot_mat {rotation_matrix(radians_per_point, direction)};
    vec3 perpendicular_dir = direction.cross(direction.y != 0 ? vec3{1,0,0} : vec3{0,1,0}).normalize();
    vec3 point = parent_position + perpendicular_dir * radius;
    for (int i = 0; i < nr_points; i++)
    {
        point = rot_mat * (point - parent_position) + parent_position;

        data.vertices.push_back(point.x);
        data.vertices.push_back(point.y);
        data.vertices.push_back(point.z);

        data.texture_coords.push_back(i / static_cast<float>(nr_points));
        data.texture_coords.push_back(0);

        data.normals.push_back(0);
        data.normals.push_back(0);
        data.normals.push_back(0);
    }

    //upper midpoint
    vec3 current_node_postion {parent_position + direction * length};
    data.vertices.push_back(current_node_postion.x);
    data.vertices.push_back(current_node_postion.y);
    data.vertices.push_back(current_node_postion.z);
    data.texture_coords.push_back(0);
    data.texture_coords.push_back(0);
    data.normals.push_back(0);
    data.normals.push_back(0);
    data.normals.push_back(0);

    //upper surounding points
    point = current_node_postion + perpendicular_dir * radius;
    for (int i = 0; i < nr_points; i++)
    {
        point = rot_mat * (point - current_node_postion) + current_node_postion;

        data.vertices.push_back(point.x);
        data.vertices.push_back(point.y);
        data.vertices.push_back(point.z);

        data.texture_coords.push_back(i / static_cast<float>(nr_points));
        data.texture_coords.push_back(1);

        data.normals.push_back(0);
        data.normals.push_back(0);
        data.normals.push_back(0);
    }

    // == Add Indices Data ==

    for (int i = 0; i < nr_points - 1; i++)
    {
        float br = i + 1; // first point is the middle
        float bl = br + 1; // next in the circle
        float tr = br + nr_points + 1; // 1 lap later + the top middle point 
        float tl = tr + 1; // next in the circle

        data.indices.push_back(nr_previously_added_vertices + bl);
        data.indices.push_back(nr_previously_added_vertices + tr);
        data.indices.push_back(nr_previously_added_vertices + tl);

        data.indices.push_back(nr_previously_added_vertices + bl);
        data.indices.push_back(nr_previously_added_vertices + br);
        data.indices.push_back(nr_previously_added_vertices + tr);
    }

    //point that wraps around
    float br = nr_points;
    float bl = 1;
    float tr = br + nr_points + 1;
    float tl = bl + nr_points + 1;

    data.indices.push_back(nr_previously_added_vertices + bl);
    data.indices.push_back(nr_previously_added_vertices + tr);
    data.indices.push_back(nr_previously_added_vertices + tl);

    data.indices.push_back(nr_previously_added_vertices + bl);
    data.indices.push_back(nr_previously_added_vertices + br);
    data.indices.push_back(nr_previously_added_vertices + tr);

    // == Add Child Data == 
    if (lateral_branch != nullptr)
    {
        lateral_branch->create_buffer_data(data, current_node_postion);
    }
    
    if (main_branch != nullptr)
    {
        main_branch->create_buffer_data(data, current_node_postion);
    }
}