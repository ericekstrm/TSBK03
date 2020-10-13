#include "Tree.h"

#include <iostream>
#include <sstream>

#include "Matrix.h"

Tree::Tree()
{
    generate();
    load_buffer_data();
}

Tree::~Tree()
{
    delete root;
}

void Tree::render(Tree_Shader const& shader) const
{
    glBindVertexArray(model_data.vao);

    shader.load_model_matrix(get_model_matrix());

    glDrawElements(GL_LINES, model_data.indices_count, GL_UNSIGNED_INT, 0);
}

void Tree::update(float delta_time)
{
    root->test_extend();
    vertices = root->generate_skeleton(position);
    load_buffer_data();
}

void Tree::generate()
{
    root = new Node(vec3{0,1,0});

    std::cout << root->to_string() << std::endl;

    vertices = root->generate_skeleton(position);
}

void Tree::load_buffer_data()
{
    glGenVertexArrays(1, &model_data.vao);
    glBindVertexArray(model_data.vao);

    int vertices_attrib_array = 0;
    glGenBuffers(1, &model_data.vb);
    glBindBuffer(GL_ARRAY_BUFFER, model_data.vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(vertices_attrib_array, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    std::vector<int> i(vertices.size());
    std::generate(i.begin(), i.end(), [i = 0]() mutable {
        return i++;
    });

    glGenBuffers(1, &model_data.ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model_data.ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * i.size(), &i[0], GL_STATIC_DRAW);
    model_data.indices_count = i.size();

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// ==============
// ===| Node |===
// ==============

Node::Node()
{

}

Node::Node(vec3 const& direction)
    : direction {direction}
{
}

Node::Node(Node* main, Node* lateral)
    : main_branch {main}, lateral_branch {lateral}
{
}

Node::~Node()
{
    delete main_branch;
    delete lateral_branch;
}

void Node::test_extend()
{
    if (main_branch == nullptr)
    {
        main_branch = new Node(direction);
    }
    else if (lateral_branch == nullptr)
    {
        vec3 random_vector {(float) rand() / RAND_MAX - 0.5f, (float)rand() / RAND_MAX - 0.5f, (float)rand() / RAND_MAX - 0.5f};
        vec3 shifted_direction {rotation_matrix( 30, random_vector) * direction};
        lateral_branch = new Node(shifted_direction);
    }
    else
    {
        if (main_branch != nullptr)
        {
            main_branch->test_extend();
        }
        if (lateral_branch != nullptr)
        {
            lateral_branch->test_extend();
        }
    }
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

std::vector<float> Node::generate_skeleton(vec3 const& parent_position) const
{
    std::vector<float> skeleton {};

    //add own skeleton
    skeleton.push_back(parent_position[0]);
    skeleton.push_back(parent_position[1]);
    skeleton.push_back(parent_position[2]);

    vec3 current_node_postion {parent_position + direction * length};

    skeleton.push_back(current_node_postion[0]);
    skeleton.push_back(current_node_postion[1]);
    skeleton.push_back(current_node_postion[2]);

    //add child skeletons
    if (lateral_branch != nullptr)
    {
        std::vector<float> lateral_skeleton = lateral_branch->generate_skeleton(current_node_postion);
        skeleton.insert(skeleton.end(), lateral_skeleton.begin(), lateral_skeleton.end());
    }
    
    if (main_branch != nullptr)
    {
        std::vector<float> main_skeleton = main_branch->generate_skeleton(current_node_postion);
        skeleton.insert(skeleton.end(), main_skeleton.begin(), main_skeleton.end());
    }
    return skeleton;
}