#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();


    void uartMsgRdy();

    void screen1ButtonClicked(int button);
    void screen1Button2Clicked(int button);

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
