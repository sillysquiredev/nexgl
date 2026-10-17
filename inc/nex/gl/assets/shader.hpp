#pragma once

#include "../../core/asset.hpp"
#include "../../gl/defines.hpp"

#include <fstream>
#include <vector>

namespace NEX::GL
{
    struct VertexShader
    {
        GLuint id = 0;

        VertexShader(std::ifstream&);
        VertexShader(std::string);
        ~VertexShader();
    };

    struct FragmentShader
    {
        GLuint id = 0;

        FragmentShader(std::ifstream&);
        FragmentShader(std::string);
        ~FragmentShader();
    };

    struct Shader : public Core::IAsset
    {
        GLuint id = 0;

        void use();
        Shader(std::string, std::string);
        Shader(const VertexShader&, const FragmentShader&);

        void set_uniform(std::string const, int);
        void set_uniform(std::string const, float);
        void set_uniform(std::string const, double);
        void set_uniform(std::string const, int const*, int);
        void set_uniform(std::string const, std::vector<int> const&);
        ~Shader();
    };
}; // namespace NEX::GL
