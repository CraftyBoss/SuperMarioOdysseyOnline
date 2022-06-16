/**
 * @file Shader.h
 * @brief Defines a basic shader.
 */

#pragma once

#include "types.h"

namespace agl
{
    enum ShaderType
    {
        ShaderType_Vertex = 0,
        ShaderType_Fragment = 1,
        ShaderType_Geometry = 2,
        ShaderType_Compute = 3
    };

    class Shader
    {
    public:
        Shader();

        virtual ~Shader();

        virtual s32 getShaderType() const = 0;
        virtual s32 getShaderMode() const;
        virtual s32 getRingItemSize() const;

        void setBinary(void const *shaderBinary);

        void* mShaderBinary; // _8
        u64 _10;
        u64 _18;
    };

    class VertexShader : public agl::Shader
    {
    public:
        virtual ~VertexShader();

        virtual s32 getShaderType() const;
    };

    class FragmentShader : public agl::Shader
    {
    public:
        virtual ~FragmentShader();

        virtual s32 getShaderType() const;
    };

    class GeometryShader : public agl::Shader
    {
    public:
        virtual ~GeometryShader();

        virtual s32 getShaderType() const;
    };

    class ComputeShader : public agl::Shader
    {
    public:
        virtual ~ComputeShader();

        virtual s32 getShaderType() const;
    };
};