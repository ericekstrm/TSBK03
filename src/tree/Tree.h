#pragma once

#include <string>
#include <vector>

#include "Vector.h"
#include "Model.h"

class Node;

class Tree : public Model
{
public:
    Tree();
    ~Tree();

    void render(Tree_Shader const& shader) const;
    void update(float delta_time);

private:

    //tmp function
    void generate();

    void load_buffer_data();

    std::vector<float> vertices = {};
    std::vector<float> normals {};
    std::vector<float> texture_coords = {};
    std::vector<int> indices = {};

    Node* root;
};

class Node
{
public:
    Node();
    Node(vec3 const& direction);
    Node(Node* main, Node* lateral);
    ~Node();

    void test_extend();

    std::string to_string() const;
    std::vector<float> generate_skeleton(vec3 const& parent_position) const;

private:

    // Internode
    //  - length (constant?)
    //  - radius (use later)

    vec3 direction;
    float length {1};
    
    // Bud
    //  - terminal
    //  - axillary/lateral
    bool has_terminal_bud {true};
    bool has_lateral_bud {false};

    Node* parent;
    Node* main_branch {nullptr};
    Node* lateral_branch {nullptr};

};
