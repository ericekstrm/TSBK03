#pragma once

#include "Model.h"

#include <string>

class Loader
{
public:

    static Model load_model(std::string const& file_name);

private:
    static std::string model_obj_folder;

};
