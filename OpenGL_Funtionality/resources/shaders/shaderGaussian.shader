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

layout(location = 0)
out vec4 color;
in vec2 v_TexCoord;

const float offset = 1.0/768;

uniform sampler2D u_Texture;

void main()
{
   vec2 offsets[9] = vec2[](vec2(-offset,offset),
      vec2(0.0f,offset),
      vec2(offset,offset),
      vec2(-offset,0.0f),
      vec2(0.0f,0.0f),
      vec2(offset,0.0f),
      vec2(-offset,-offset),
      vec2(0.0f,-offset),
      vec2(offset,-offset)
   );

   float kernel[9] = float[](
      1.0 / 16,2.0 / 16, 1.0 / 16,
      2.0 / 16,4.0 / 16, 2.0 / 16,
      1.0 / 16,2.0 / 16, 1.0 / 16
   );

   vec3 sampleTex[9];

   for(int i = 0 ; i < 9 ; i++){
      sampleTex[i] = vec3(texture(u_Texture,v_TexCoord.st + offsets[i]));
   }

   vec3 col;

   for(int i = 0 ; i < 9 ; i++){
      col += sampleTex[i] * kernel[i];
   }

   color = vec4(col,1.0);


   // vec4 texColor = texture(u_Texture,v_TexCoord);
   // float average = (texColor.r + texColor.g + texColor.b) / 3.0f;
   // color = vec4(average,average,average,1.0);
};