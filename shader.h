#include <QColor>
#include <QSGSimpleMaterialShader>

struct State
{
    QColor color;

    int compare(const State *other) const;
};

class Shader : public QSGSimpleMaterialShader<State>
{
    QSG_DECLARE_SIMPLE_COMPARABLE_SHADER(Shader, State);

public:

    const char *vertexShader() const;

    const char *fragmentShader() const;

    QList<QByteArray> attributes() const;

    void updateState(const State *state, const State *);

    void resolveUniforms();

private:
    int id_color;

};
