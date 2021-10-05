#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::uartMsgRdy()
{
	view.uartMsgRdy();
}

void Screen1Presenter::buttonClicked(int button)
{
	model->screen1ButtonClicked(button);
}

void Screen1Presenter::button2Clicked(int button)
{
	model->screen1Button2Clicked(button);
}
