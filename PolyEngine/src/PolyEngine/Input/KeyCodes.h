#pragma once
namespace PolyEngine
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define POLY_KEY_SPACE           ::PolyEngine::Key::Space
#define POLY_KEY_APOSTROPHE      ::PolyEngine::Key::Apostrophe    /* ' */
#define POLY_KEY_COMMA           ::PolyEngine::Key::Comma         /* , */
#define POLY_KEY_MINUS           ::PolyEngine::Key::Minus         /* - */
#define POLY_KEY_PERIOD          ::PolyEngine::Key::Period        /* . */
#define POLY_KEY_SLASH           ::PolyEngine::Key::Slash         /* / */
#define POLY_KEY_0               ::PolyEngine::Key::D0
#define POLY_KEY_1               ::PolyEngine::Key::D1
#define POLY_KEY_2               ::PolyEngine::Key::D2
#define POLY_KEY_3               ::PolyEngine::Key::D3
#define POLY_KEY_4               ::PolyEngine::Key::D4
#define POLY_KEY_5               ::PolyEngine::Key::D5
#define POLY_KEY_6               ::PolyEngine::Key::D6
#define POLY_KEY_7               ::PolyEngine::Key::D7
#define POLY_KEY_8               ::PolyEngine::Key::D8
#define POLY_KEY_9               ::PolyEngine::Key::D9
#define POLY_KEY_SEMICOLON       ::PolyEngine::Key::Semicolon     /* ; */
#define POLY_KEY_EQUAL           ::PolyEngine::Key::Equal         /* = */
#define POLY_KEY_A               ::PolyEngine::Key::A
#define POLY_KEY_B               ::PolyEngine::Key::B
#define POLY_KEY_C               ::PolyEngine::Key::C
#define POLY_KEY_D               ::PolyEngine::Key::D
#define POLY_KEY_E               ::PolyEngine::Key::E
#define POLY_KEY_F               ::PolyEngine::Key::F
#define POLY_KEY_G               ::PolyEngine::Key::G
#define POLY_KEY_H               ::PolyEngine::Key::H
#define POLY_KEY_I               ::PolyEngine::Key::I
#define POLY_KEY_J               ::PolyEngine::Key::J
#define POLY_KEY_K               ::PolyEngine::Key::K
#define POLY_KEY_L               ::PolyEngine::Key::L
#define POLY_KEY_M               ::PolyEngine::Key::M
#define POLY_KEY_N               ::PolyEngine::Key::N
#define POLY_KEY_O               ::PolyEngine::Key::O
#define POLY_KEY_P               ::PolyEngine::Key::P
#define POLY_KEY_Q               ::PolyEngine::Key::Q
#define POLY_KEY_R               ::PolyEngine::Key::R
#define POLY_KEY_S               ::PolyEngine::Key::S
#define POLY_KEY_T               ::PolyEngine::Key::T
#define POLY_KEY_U               ::PolyEngine::Key::U
#define POLY_KEY_V               ::PolyEngine::Key::V
#define POLY_KEY_W               ::PolyEngine::Key::W
#define POLY_KEY_X               ::PolyEngine::Key::X
#define POLY_KEY_Y               ::PolyEngine::Key::Y
#define POLY_KEY_Z               ::PolyEngine::Key::Z
#define POLY_KEY_LEFT_BRACKET    ::PolyEngine::Key::LeftBracket   /* [ */
#define POLY_KEY_BACKSLASH       ::PolyEngine::Key::Backslash     /* \ */
#define POLY_KEY_RIGHT_BRACKET   ::PolyEngine::Key::RightBracket  /* ] */
#define POLY_KEY_GRAVE_ACCENT    ::PolyEngine::Key::GraveAccent   /* ` */
#define POLY_KEY_WORLD_1         ::PolyEngine::Key::World1        /* non-US #1 */
#define POLY_KEY_WORLD_2         ::PolyEngine::Key::World2        /* non-US #2 */

/* Function keys */
#define POLY_KEY_ESCAPE          ::PolyEngine::Key::Escape
#define POLY_KEY_ENTER           ::PolyEngine::Key::Enter
#define POLY_KEY_TAB             ::PolyEngine::Key::Tab
#define POLY_KEY_BACKSPACE       ::PolyEngine::Key::Backspace
#define POLY_KEY_INSERT          ::PolyEngine::Key::Insert
#define POLY_KEY_DELETE          ::PolyEngine::Key::Delete
#define POLY_KEY_RIGHT           ::PolyEngine::Key::Right
#define POLY_KEY_LEFT            ::PolyEngine::Key::Left
#define POLY_KEY_DOWN            ::PolyEngine::Key::Down
#define POLY_KEY_UP              ::PolyEngine::Key::Up
#define POLY_KEY_PAGE_UP         ::PolyEngine::Key::PageUp
#define POLY_KEY_PAGE_DOWN       ::PolyEngine::Key::PageDown
#define POLY_KEY_HOME            ::PolyEngine::Key::Home
#define POLY_KEY_END             ::PolyEngine::Key::End
#define POLY_KEY_CAPS_LOCK       ::PolyEngine::Key::CapsLock
#define POLY_KEY_SCROLL_LOCK     ::PolyEngine::Key::ScrollLock
#define POLY_KEY_NUM_LOCK        ::PolyEngine::Key::NumLock
#define POLY_KEY_PRINT_SCREEN    ::PolyEngine::Key::PrintScreen
#define POLY_KEY_PAUSE           ::PolyEngine::Key::Pause
#define POLY_KEY_F1              ::PolyEngine::Key::F1
#define POLY_KEY_F2              ::PolyEngine::Key::F2
#define POLY_KEY_F3              ::PolyEngine::Key::F3
#define POLY_KEY_F4              ::PolyEngine::Key::F4
#define POLY_KEY_F5              ::PolyEngine::Key::F5
#define POLY_KEY_F6              ::PolyEngine::Key::F6
#define POLY_KEY_F7              ::PolyEngine::Key::F7
#define POLY_KEY_F8              ::PolyEngine::Key::F8
#define POLY_KEY_F9              ::PolyEngine::Key::F9
#define POLY_KEY_F10             ::PolyEngine::Key::F10
#define POLY_KEY_F11             ::PolyEngine::Key::F11
#define POLY_KEY_F12             ::PolyEngine::Key::F12
#define POLY_KEY_F13             ::PolyEngine::Key::F13
#define POLY_KEY_F14             ::PolyEngine::Key::F14
#define POLY_KEY_F15             ::PolyEngine::Key::F15
#define POLY_KEY_F16             ::PolyEngine::Key::F16
#define POLY_KEY_F17             ::PolyEngine::Key::F17
#define POLY_KEY_F18             ::PolyEngine::Key::F18
#define POLY_KEY_F19             ::PolyEngine::Key::F19
#define POLY_KEY_F20             ::PolyEngine::Key::F20
#define POLY_KEY_F21             ::PolyEngine::Key::F21
#define POLY_KEY_F22             ::PolyEngine::Key::F22
#define POLY_KEY_F23             ::PolyEngine::Key::F23
#define POLY_KEY_F24             ::PolyEngine::Key::F24
#define POLY_KEY_F25             ::PolyEngine::Key::F25

/* Keypad */
#define POLY_KEY_KP_0            ::PolyEngine::Key::KP0
#define POLY_KEY_KP_1            ::PolyEngine::Key::KP1
#define POLY_KEY_KP_2            ::PolyEngine::Key::KP2
#define POLY_KEY_KP_3            ::PolyEngine::Key::KP3
#define POLY_KEY_KP_4            ::PolyEngine::Key::KP4
#define POLY_KEY_KP_5            ::PolyEngine::Key::KP5
#define POLY_KEY_KP_6            ::PolyEngine::Key::KP6
#define POLY_KEY_KP_7            ::PolyEngine::Key::KP7
#define POLY_KEY_KP_8            ::PolyEngine::Key::KP8
#define POLY_KEY_KP_9            ::PolyEngine::Key::KP9
#define POLY_KEY_KP_DECIMAL      ::PolyEngine::Key::KPDecimal
#define POLY_KEY_KP_DIVIDE       ::PolyEngine::Key::KPDivide
#define POLY_KEY_KP_MULTIPLY     ::PolyEngine::Key::KPMultiply
#define POLY_KEY_KP_SUBTRACT     ::PolyEngine::Key::KPSubtract
#define POLY_KEY_KP_ADD          ::PolyEngine::Key::KPAdd
#define POLY_KEY_KP_ENTER        ::PolyEngine::Key::KPEnter
#define POLY_KEY_KP_EQUAL        ::PolyEngine::Key::KPEqual

#define POLY_KEY_LEFT_SHIFT      ::PolyEngine::Key::LeftShift
#define POLY_KEY_LEFT_CONTROL    ::PolyEngine::Key::LeftControl
#define POLY_KEY_LEFT_ALT        ::PolyEngine::Key::LeftAlt
#define POLY_KEY_LEFT_SUPER      ::PolyEngine::Key::LeftSuper
#define POLY_KEY_RIGHT_SHIFT     ::PolyEngine::Key::RightShift
#define POLY_KEY_RIGHT_CONTROL   ::PolyEngine::Key::RightControl
#define POLY_KEY_RIGHT_ALT       ::PolyEngine::Key::RightAlt
#define POLY_KEY_RIGHT_SUPER     ::PolyEngine::Key::RightSuper
#define POLY_KEY_MENU            ::PolyEngine::Key::Menu