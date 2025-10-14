R"(
#version 330 core
out vec4 FragColor;

in vec4 vColor;
in vec2 vTexCoord;
in float vTexIndex;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform sampler2D uTexture3;
uniform sampler2D uTexture4;
uniform sampler2D uTexture5;
uniform sampler2D uTexture6;
uniform sampler2D uTexture7;
uniform sampler2D uTexture8;
uniform sampler2D uTexture9;
uniform sampler2D uTexture10;
uniform sampler2D uTexture11;
uniform sampler2D uTexture12;
uniform sampler2D uTexture13;
uniform sampler2D uTexture14;
uniform sampler2D uTexture15;

void main() {
   vec4 texColor = vec4(1.0);
   int index = int(vTexIndex);
   if (index == 0) {
      texColor = texture(uTexture0, vTexCoord);
   }
   if (index == 1) {
      texColor = texture(uTexture1, vTexCoord);
   }
   if (index == 2) {
      texColor = texture(uTexture2, vTexCoord);
   }
   if (index == 3) {
      texColor = texture(uTexture3, vTexCoord);
   }
   if (index == 4) {
      texColor = texture(uTexture4, vTexCoord);
   }
   if (index == 5) {
      texColor = texture(uTexture5, vTexCoord);
   }
   if (index == 6) {
      texColor = texture(uTexture6, vTexCoord);
   }
   if (index == 7) {
      texColor = texture(uTexture7, vTexCoord);
   }
   if (index == 8) {
      texColor = texture(uTexture8, vTexCoord);
   }
   if (index == 9) {
      texColor = texture(uTexture9, vTexCoord);
   }
   if (index == 10) {
      texColor = texture(uTexture10, vTexCoord);
   }
   if (index == 11) {
      texColor = texture(uTexture11, vTexCoord);
   }
   if (index == 12) {
      texColor = texture(uTexture12, vTexCoord);
   }
   if (index == 13) {
      texColor = texture(uTexture13, vTexCoord);
   }
   if (index == 14) {
      texColor = texture(uTexture14, vTexCoord);
   }
   if (index == 15) {
      texColor = texture(uTexture15, vTexCoord);
   }
   if (vColor.w == 1.0) { // text
      vec4 sampled = vec4(1.0, 1.0, 1.0, texColor.r);
      FragColor = vec4(vColor.xyz, 1.0) * sampled;
   } else {
      FragColor = vec4(vColor.xyz, 1.0) * texColor;
   }
}
)"