union Keys
{
	enum key 
	{
		// ascii keys go first
		K_None,
		K_Backspace = 8,
		K__Tab,
		K_Enter = 13,
		K_Escape = 27,
		K_Space = 32,
		K_Exclaim,
		K_DblQuote,
		K_Hash,
		K_Dollar,
		K_Percent,
		K_Ampersand,
		K_Quote,
		K_LeftParen,
		K_RightParen,
		K_Asterisk,
		K_Plus,
		K_Comma,
		K_Minus,
		K_Period,
		K_ForewardSlash,
		K_0,
		K_1,
		K_2,
		K_3,
		K_4,
		K_5,
		K_6,
		K_7,
		K_8,
		K_9,
		K_Colon,
		K_SemiColon,
		K_LessThan,
		K_Equals,
		K_GreaterThan,
		K_Question,
		K_At,
		K_LeftBrack = 91,
		K_Caret,
		K_Underscore,
		K_BckQuote,
		K_a,
		K_b,
		K_c,
		K_d,
		K_e,
		K_f,
		K_g,
		K_h,
		K_i,
		K_j,
		K_k,
		K_l,
		K_m,
		K_n,
		K_o,
		K_p,
		K_q,
		K_r,
		K_s,
		K_t,
		K_u,
		K_v,
		K_w,
		K_x,
		K_y,
		K_z,
		K_LeftCurly,
		K_Pipe,
		K_RightCurly,
		K_Tilde,
		K_Delete,

		ASCII_END = 255,

		K_F1,
		K_F2,
		K_F3,
		K_F4,
		K_F5,
		K_F6,
		K_F7,
		K_F8,
		K_F9,
		K_F10,
		K_F11,
		K_F12,

		K_Up,
		K_Right,
		K_Down,
		K_Left,
	};

	int val;
};