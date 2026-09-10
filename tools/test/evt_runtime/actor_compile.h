#pragma once

// The host test does not render battle UI. Avoid a union-typed argument that GCC rejects in an unused function.
#define draw_box(...) 0
