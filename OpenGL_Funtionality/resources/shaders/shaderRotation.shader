#shader vertex
#version 330 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texCoord;

uniform mat4 transform;

out vec2 v_TexCoord;

void main()
{
   gl_Position = transform *vec4(positions,1.0f);
   v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
   vec4 texColor = texture(u_Texture,v_TexCoord);
   color = texColor;
};