#include "face.h"

#include <vector>
#include <unordered_map>

namespace {

std::vector <std::string> face_strings = { "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A" };

std::unordered_map <std::string, uint8_t> build_face_string_to_value_map() {
    std::unordered_map <std::string, uint8_t> map;
    for (size_t i = 0; i < NFACES; i++)
        map[face_strings[i]] = i;
    return map;
};

uint8_t face_string_to_value(const std::string& str) {
    static const std::unordered_map<std::string, uint8_t> map = build_face_string_to_value_map();
    return map.at(str);
}

std::vector<Face> build_all_faces() {
    std::vector<Face> vec;
    for (uint8_t i = 0; i < NFACES; i++)
        vec.push_back(Face(i));
    return vec;
}

}  // namespace

Face::Face(const std::string& str) : _value(face_string_to_value(str)) {}

const std::string& Face::string() { return face_strings.at(_value); }

const std::vector<Face>& all_faces() {
    static std::vector<Face> faces = build_all_faces();
    return faces;
}

Face Face::ace("A");
Face Face::two("2");
Face Face::five("5");
