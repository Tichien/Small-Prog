#include <iostream>
#include <string>
#include "Clock.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ConsoleWindow.h"
#include "Console.h"

using namespace std;

#define ESCAPE 27

void handler(ConsoleWindow& w);

int main(){
	Console::startPowerMode(); 
	
	ConsoleWindow w(3, 3, 20, 20);
	w.fill(ConsoleColor::WhiteGreen, Attribute::Normal);
	w.setColor(ConsoleColor::WhiteGreen);
	//w.setAttribute(Attribute::Bold);
	w.write("text rouge");
	w.write("text vert clair", ConsoleColor::WhiteGreen, Attribute::Bold);
	w.write("text rouge");
	w.setBorder(Window::BorderType::Diamond, ConsoleColor(Red, Black), Attribute::HalfBright);


	Cellule cell = w.getCellule(0, 0);
	mvaddch(0, 0, cell);
	Cellule cell2('X', ConsoleColor::WhiteBlack, Attribute::Bold);
	Console::Screen.write("truc");
	Console::Screen.setBorder(Window::BorderType::Thin);

	Clock t;

	while(Console::Screen.read() != ESCAPE){


		
		//if(t.getElapsedTime() > (float)1/30){
		//}


		//if(t.getElapsedTime() > (float)1/120){
			
			//Console::Screen.write(t.toString(), 1, 1);

			t.restart();


			//Console::Screen.read();

			handler(w);

			Console::Screen.clear();


			if(Keyboard::isKeyPressed(Keyboard::Key::K))
				w.clear();

			//Console::Screen.write("attention 1 sec", 1, 2);

			//w.write(t.toString(), 1, 1);
			w.write(w.getPosition().toString(), 1, 2);
			w.write(w.getSize().toString(), 1, 3);
			w.display();
		//}

	}
	Console::endPowerMode();
	return 0;
}

void handler(ConsoleWindow& w){

	if(Keyboard::isKeyPressed(Keyboard::Key::Z)){
		w.setSize(w.getSize() + Vector2i::Up);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Q)){
		w.setSize(w.getSize() + Vector2i::Left);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::S)){ 
		w.setSize(w.getSize() + Vector2i::Down);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::D)){
		w.setSize(w.getSize() + Vector2i::Right);
	}

	else if(Keyboard::isKeyPressed(Keyboard::Key::Up)){
		w.setPosition(w.getPosition() + Vector2i::Up);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Left)){
		w.setPosition(w.getPosition() + Vector2i::Left);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Down)){
		w.setPosition(w.getPosition() + Vector2i::Down);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Right)){
		w.setPosition(w.getPosition() + Vector2i::Right);
	}
	else if(Mouse::isButtonPressed(Mouse::Button::Right)){

	}
	else if(Mouse::isButtonPressed(Mouse::Button::Left)){
		w.setPosition(Mouse::getPosition());
	}
}
