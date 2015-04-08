#include "shader.h"


int State::compare(const State* other) const {
    uint rgb = color.rgba();
    uint otherRgb = other->color.rgba();

    if (rgb == otherRgb) {
        return 0;
    } else if (rgb < otherRgb) {
        return -1;
    } else {
        return 1;
    }
}


const char*Shader::vertexShader() const {
    return
            "attribute highp vec4 aVertex;                              \n"
            "attribute highp vec2 aTexCoord;                            \n"
            "uniform highp mat4 qt_Matrix;                              \n"
            "varying highp vec2 texCoord;                               \n"
            "void main() {                                              \n"
            "    gl_Position = qt_Matrix * aVertex;                     \n"
            "    texCoord = aTexCoord;                                  \n"
            "}";
}

const char*Shader::fragmentShader() const {
    return
            "uniform lowp float qt_Opacity;                             \n"
            "uniform lowp vec4 color;                                   \n"
            "varying highp vec2 texCoord;                               \n"
            "void main ()                                               \n"
            "{                                                          \n"
            "    gl_FragColor = (1.0-(sqrt(pow(texCoord.y-0.5,2)+pow(texCoord.x-0.5,2))+0.2f)) * color * qt_Opacity *1.0 ;  \n"
            "}";
}

QList<QByteArray> Shader::attributes() const{
    return QList<QByteArray>() << "aVertex" << "aTexCoord";
}

void Shader::updateState(const State* state, const State*){
    program()->setUniformValue(id_color, state->color);
}

void Shader::resolveUniforms()
{
    id_color = program()->uniformLocation("color");
}
