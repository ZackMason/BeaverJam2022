#version 460 core
out vec4 FragColor;

in vec2 voPos;
in vec2 voUV;
flat in int voTexture;

uniform sampler2D uTextures[32];

void main() {
    vec4 color = texture(uTextures[voTexture], voUV);
    if (color.a < 0.1) discard;
    FragColor = pow(color, vec4(2.2));
}