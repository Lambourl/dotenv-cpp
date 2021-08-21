#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <dotenv/pre/usefile/usefile.hpp>
#include <dotenv/pre/common/common.hpp>
#include <dotenv/pre/formap/formap.hpp>

namespace dotenv {

  inline void use_dotenv_file(std::string path_filename, bool preserve = true) {
    std::vector<std::map<std::string, std::string>> vector_of_future_env =
        dotenv::pre::usefile::read_file_dotenv(path_filename);
    bool contains_ref;
    do {
      dotenv::pre::usefile::transform_in_final_vector(vector_of_future_env);
      contains_ref = dotenv::pre::usefile::is_vector_contains_ref(vector_of_future_env);
    } while (contains_ref);

    if (!(preserve)) {
      dotenv::pre::usefile::set_environment_without_preserve(vector_of_future_env);
    } else {
      dotenv::pre::usefile::set_environment_with_preserve(vector_of_future_env);
    }
  }

  inline void getenv_or_value(std::string environment_name, std::string default_value) {
    if (!(std::getenv(environment_name.c_str()))) {
      dotenv::pre::common::set_environment(environment_name.c_str(), default_value.c_str());
    }
  }

  inline void use_dotenv_map(std::map<std::string, std::string> futur_env, bool preserve = true) {
    bool contains_ref;
    do {
      dotenv::pre::formap::transform_in_final_map(futur_env);
      contains_ref = dotenv::pre::formap::is_map_contains_ref(futur_env);
    } while (contains_ref);

    if (preserve) {
      dotenv::pre::formap::set_environment_with_preserve_for_map(futur_env);
    } else {
      dotenv::pre::formap::set_environment_without_preserve_for_map(futur_env);
    }
    dotenv::pre::formap::print_map_to_display(futur_env);
  }
}