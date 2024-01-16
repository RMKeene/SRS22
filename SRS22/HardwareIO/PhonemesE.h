#pragma once

/// <summary>
/// Phoneme keys. Never change the order of these, never delete any. MAXENUM must always be last.
/// </summary>
enum class PhonemeE {
	SPACE = 0,

	A, AE, AH, B, D, DH, E, EE,
	F, G, I, IE, K, L, M, N,
	NY, OH, OO, P, R, S, SH, T,
	TH, V, W, X, Z, ZH,

	// Insert new phonemes here.

	MAXENUM
};
