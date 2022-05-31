#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;


uniform sampler2D ourFace;
uniform sampler2D ourTexture;

out vec4 FragColor;
void main(){
    FragColor = mix(texture(ourTexture,TexCoord),texture(ourFace,TexCoord),0.2);
}
