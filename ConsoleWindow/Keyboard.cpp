#include "Keyboard.h"
#include "Console.h"

bool Keyboard::isKeyPressed(Key key) {

	int consoleInput = Console::Screen.getInput();

	switch (key)
	{
	case Keyboard::A:
		return consoleInput == 'a' || consoleInput == 'A';
		break;
	case Keyboard::B:
		return consoleInput == 'b' || consoleInput == 'B';
		break;
	case Keyboard::C:
		return consoleInput == 'c' || consoleInput == 'C';
		break;
	case Keyboard::D:
		return consoleInput == 'd' || consoleInput == 'D';
		break;
	case Keyboard::E:
		return consoleInput == 'e' || consoleInput == 'E';
		break;
	case Keyboard::F:
		return consoleInput == 'f' || consoleInput == 'F';
		break;
	case Keyboard::G:
		return consoleInput == 'g' || consoleInput == 'G';
		break;
	case Keyboard::H:
		return consoleInput == 'h' || consoleInput == 'H';
		break;
	case Keyboard::I:
		return consoleInput == 'i' || consoleInput == 'I';
		break;
	case Keyboard::J:
		return consoleInput == 'j' || consoleInput == 'J';
		break;
	case Keyboard::K:
		return consoleInput == 'k' || consoleInput == 'K';
		break;
	case Keyboard::L:
		return consoleInput == 'l' || consoleInput == 'L';
		break;
	case Keyboard::M:
		return consoleInput == 'm' || consoleInput == 'M';
		break;
	case Keyboard::N:
		return consoleInput == 'n' || consoleInput == 'N';
		break;
	case Keyboard::O:
		return consoleInput == 'o' || consoleInput == 'O';
		break;
	case Keyboard::P:
		return consoleInput == 'p' || consoleInput == 'P';
		break;
	case Keyboard::Q:
		return consoleInput == 'q' || consoleInput == 'Q';
		break;
	case Keyboard::R:
		return consoleInput == 'r' || consoleInput == 'R';
		break;
	case Keyboard::S:
		return consoleInput == 's' || consoleInput == 'S';
		break;
	case Keyboard::T:
		return consoleInput == 't' || consoleInput == 'T';
		break;
	case Keyboard::U:
		return consoleInput == 'u' || consoleInput == 'U';
		break;
	case Keyboard::V:
		return consoleInput == 'v' || consoleInput == 'V';
		break;
	case Keyboard::W:
		return consoleInput == 'w' || consoleInput == 'W';
		break;
	case Keyboard::X:
		return consoleInput == 'x' || consoleInput == 'X';
		break;
	case Keyboard::Y:
		return consoleInput == 'y' || consoleInput == 'Y';
		break;
	case Keyboard::Z:
		return consoleInput == 'z' || consoleInput == 'Z';
		break;
	case Keyboard::Num0:
		return consoleInput == 224 || consoleInput == '0'; //problème avec la reconnaissance de 'à' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Num1:
		return consoleInput == '&' || consoleInput == '1';
		break;
	case Keyboard::Num2:
		return consoleInput == 233 || consoleInput == '2';  //problème avec la reconnaissance de 'é' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Num3:
		return consoleInput == '\"' || consoleInput == '3';
		break;
	case Keyboard::Num4:
		return consoleInput == '\'' || consoleInput == '4';
		break;
	case Keyboard::Num5:
		return consoleInput == '(' || consoleInput == '5';
		break;
	case Keyboard::Num6:
		return consoleInput == '-' || consoleInput == '6';
		break;
	case Keyboard::Num7:
		return consoleInput == 232 || consoleInput == '7';  //problème avec la reconnaissance de 'è' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Num8:
		return consoleInput == '_' || consoleInput == '8';
		break;
	case Keyboard::Num9:
		return consoleInput == 231 || consoleInput == '9';  //problème avec la reconnaissance de 'ç' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Escape:
		return consoleInput == 27; //Surement probleme de compatibilité
		break;
	case Keyboard::SemiColon:
		return consoleInput == ';' || consoleInput == '.';
		break;
	case Keyboard::Comma:
		return consoleInput == ',' || consoleInput == '?';
		break;
	case Keyboard::Period:
		return consoleInput == '<' || consoleInput == '>';
		break;
	case Keyboard::Equal:
		return consoleInput == '=' || consoleInput == '+';
		break;
	case Keyboard::Space:
		return consoleInput == ' ';
		break;
	case Keyboard::Return:
		return consoleInput == KEY_ENTER || consoleInput == 13 || consoleInput == 10; //Surement probleme de compatibilité
		break;
	case Keyboard::BackSpace:
		return consoleInput == KEY_BACKSPACE || consoleInput == 8; //Surement probleme de compatibilité
		break;
	case Keyboard::Tab:
		return consoleInput == KEY_BTAB || consoleInput == 9; //Surement probleme de compatibilité
		break;
	case Keyboard::Left:
		return consoleInput == KEY_LEFT;
		break;
	case Keyboard::Right:
		return consoleInput == KEY_RIGHT;
		break;
	case Keyboard::Up:
		return consoleInput == KEY_UP;
		break;
	case Keyboard::Down:
		return consoleInput == KEY_DOWN;
		break;
	case Keyboard::Numpad0:
		return consoleInput == '0';
		break;
	case Keyboard::Numpad1:
		return consoleInput == '1';
		break;
	case Keyboard::Numpad2:
		return consoleInput == '2';
		break;
	case Keyboard::Numpad3:
		return consoleInput == '3';
		break;
	case Keyboard::Numpad4:
		return consoleInput == '4';
		break;
	case Keyboard::Numpad5:
		return consoleInput == '5';
		break;
	case Keyboard::Numpad6:
		return consoleInput == '6';
		break;
	case Keyboard::Numpad7:
		return consoleInput == '7';
		break;
	case Keyboard::Numpad8:
		return consoleInput == '8';
		break;
	case Keyboard::Numpad9:
		return consoleInput == '9';
		break;
	case Keyboard::F1:
		return consoleInput == KEY_F(1);
		break;
	case Keyboard::F2:
		return consoleInput == KEY_F(2);
		break;
	case Keyboard::F3:
		return consoleInput == KEY_F(3);
		break;
	case Keyboard::F4:
		return consoleInput == KEY_F(4);
		break;
	case Keyboard::F5:
		return consoleInput == KEY_F(5);
		break;
	case Keyboard::F6:
		return consoleInput == KEY_F(6);
		break;
	case Keyboard::F7:
		return consoleInput == KEY_F(7);
		break;
	case Keyboard::F8:
		return consoleInput == KEY_F(8);
		break;
	case Keyboard::F9:
		return consoleInput == KEY_F(9);
		break;
	case Keyboard::F10:
		return consoleInput == KEY_F(10);
		break;
	case Keyboard::F11:
		return consoleInput == KEY_F(11);
		break;
	case Keyboard::F12:
		return consoleInput == KEY_F(12);
		break;
	default:
		break;
	}
	return false;
}
