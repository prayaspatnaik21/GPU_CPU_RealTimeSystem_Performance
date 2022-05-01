#shader vertex
#version 330 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texCoord;

uniform mat4 transform;
out vec2 TexCoords;

void main()
{
   gl_Position = transform*vec4(positions,1.0f);
   TexCoords = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) 
out vec4 color;

in vec2 TexCoords;

uniform sampler2D u_Texture;

uniform float weight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216,
                                  0.0540540541, 0.0162162162);

void main()
{
    vec2 tex_offset = 1.0/textureSize(u_Texture,0);

    vec3 result = texture(u_Texture,TexCoords).rgb * weight[0];

    for(int i = 1; i < 5 ; i++)
    {
        result += texture(u_Texture,TexCoords + vec2(tex_offset.x*i,0.0)).rgb * weight[i];

        result += texture(u_Texture,TexCoords - vec2(tex_offset.x*i,0.0)).rgb * weight[i];
    }

    color = vec4(result,1.0);
};