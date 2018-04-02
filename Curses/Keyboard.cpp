#include "Keyboard.h"
#include "Term.h"

bool Keyboard::isKeyPressed(Key key) {

	int term_input = Term::get_input();

	switch (key)
	{
	case Keyboard::A:
		return term_input == 'a' || term_input == 'A';
		break;
	case Keyboard::B:
		return term_input == 'b' || term_input == 'B';
		break;
	case Keyboard::C:
		return term_input == 'c' || term_input == 'C';
		break;
	case Keyboard::D:
		return term_input == 'd' || term_input == 'D';
		break;
	case Keyboard::E:
		return term_input == 'e' || term_input == 'E';
		break;
	case Keyboard::F:
		return term_input == 'f' || term_input == 'F';
		break;
	case Keyboard::G:
		return term_input == 'g' || term_input == 'G';
		break;
	case Keyboard::H:
		return term_input == 'h' || term_input == 'H';
		break;
	case Keyboard::I:
		return term_input == 'i' || term_input == 'I';
		break;
	case Keyboard::J:
		return term_input == 'j' || term_input == 'J';
		break;
	case Keyboard::K:
		return term_input == 'k' || term_input == 'K';
		break;
	case Keyboard::L:
		return term_input == 'l' || term_input == 'L';
		break;
	case Keyboard::M:
		return term_input == 'm' || term_input == 'M';
		break;
	case Keyboard::N:
		return term_input == 'n' || term_input == 'N';
		break;
	case Keyboard::O:
		return term_input == 'o' || term_input == 'O';
		break;
	case Keyboard::P:
		return term_input == 'p' || term_input == 'P';
		break;
	case Keyboard::Q:
		return term_input == 'q' || term_input == 'Q';
		break;
	case Keyboard::R:
		return term_input == 'r' || term_input == 'R';
		break;
	case Keyboard::S:
		return term_input == 's' || term_input == 'S';
		break;
	case Keyboard::T:
		return term_input == 't' || term_input == 'T';
		break;
	case Keyboard::U:
		return term_input == 'u' || term_input == 'U';
		break;
	case Keyboard::V:
		return term_input == 'v' || term_input == 'V';
		break;
	case Keyboard::W:
		return term_input == 'w' || term_input == 'W';
		break;
	case Keyboard::X:
		return term_input == 'x' || term_input == 'X';
		break;
	case Keyboard::Y:
		return term_input == 'y' || term_input == 'Y';
		break;
	case Keyboard::Z:
		return term_input == 'z' || term_input == 'Z';
		break;
	case Keyboard::Num0:
		return term_input == 224 || term_input == '0'; //problème avec la reconnaissance de 'à' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Num1:
		return term_input == '&' || term_input == '1';
		break;
	case Keyboard::Num2:
		return term_input == 233 || term_input == '2';  //problème avec la reconnaissance de 'é' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Num3:
		return term_input == '\"' || term_input == '3';
		break;
	case Keyboard::Num4:
		return term_input == '\'' || term_input == '4';
		break;
	case Keyboard::Num5:
		return term_input == '(' || term_input == '5';
		break;
	case Keyboard::Num6:
		return term_input == '-' || term_input == '6';
		break;
	case Keyboard::Num7:
		return term_input == 232 || term_input == '7';  //problème avec la reconnaissance de 'è' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Num8:
		return term_input == '_' || term_input == '8';
		break;
	case Keyboard::Num9:
		return term_input == 231 || term_input == '9';  //problème avec la reconnaissance de 'ç' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Escape:
		return term_input == 27; //Surement probleme de compatibilité
		break;
	case Keyboard::SemiColon:
		return term_input == ';' || term_input == '.';
		break;
	case Keyboard::Comma:
		return term_input == ',' || term_input == '?';
		break;
	case Keyboard::Period:
		return term_input == '<' || term_input == '>';
		break;
	case Keyboard::Equal:
		return term_input == '=' || term_input == '+';
		break;
	case Keyboard::Space:
		return term_input == ' ';
		break;
	case Keyboard::Return:
		return term_input == KEY_ENTER || term_input == 13 || term_input == 10; //Surement probleme de compatibilité
		break;
	case Keyboard::BackSpace:
		return term_input == KEY_BACKSPACE || term_input == 8; //Surement probleme de compatibilité
		break;
	case Keyboard::Tab:
		return term_input == KEY_BTAB || term_input == 9; //Surement probleme de compatibilité
		break;
	case Keyboard::Left:
		return term_input == KEY_LEFT;
		break;
	case Keyboard::Right:
		return term_input == KEY_RIGHT;
		break;
	case Keyboard::Up:
		return term_input == KEY_UP;
		break;
	case Keyboard::Down:
		return term_input == KEY_DOWN;
		break;
	case Keyboard::Numpad0:
		return term_input == '0';
		break;
	case Keyboard::Numpad1:
		return term_input == '1';
		break;
	case Keyboard::Numpad2:
		return term_input == '2';
		break;
	case Keyboard::Numpad3:
		return term_input == '3';
		break;
	case Keyboard::Numpad4:
		return term_input == '4';
		break;
	case Keyboard::Numpad5:
		return term_input == '5';
		break;
	case Keyboard::Numpad6:
		return term_input == '6';
		break;
	case Keyboard::Numpad7:
		return term_input == '7';
		break;
	case Keyboard::Numpad8:
		return term_input == '8';
		break;
	case Keyboard::Numpad9:
		return term_input == '9';
		break;
	case Keyboard::F1:
		return term_input == KEY_F(1);
		break;
	case Keyboard::F2:
		return term_input == KEY_F(2);
		break;
	case Keyboard::F3:
		return term_input == KEY_F(3);
		break;
	case Keyboard::F4:
		return term_input == KEY_F(4);
		break;
	case Keyboard::F5:
		return term_input == KEY_F(5);
		break;
	case Keyboard::F6:
		return term_input == KEY_F(6);
		break;
	case Keyboard::F7:
		return term_input == KEY_F(7);
		break;
	case Keyboard::F8:
		return term_input == KEY_F(8);
		break;
	case Keyboard::F9:
		return term_input == KEY_F(9);
		break;
	case Keyboard::F10:
		return term_input == KEY_F(10);
		break;
	case Keyboard::F11:
		return term_input == KEY_F(11);
		break;
	case Keyboard::F12:
		return term_input == KEY_F(12);
		break;
	default:
		break;
	}
	return false;
}
