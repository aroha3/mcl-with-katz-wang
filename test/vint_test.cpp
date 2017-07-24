#include <stdio.h>
#include <mcl/vint.hpp>
#include <iostream>
#include <sstream>
#include <set>
#ifndef _MSC_VER
#define CYBOZU_BENCH_DONT_USE_RDTSC
#define CYBOZU_BENCH_USE_GETTIMEOFDAY
#endif
#include <cybozu/benchmark.hpp>
#include <cybozu/test.hpp>

#define PUT(x) std::cout << #x "=" << x << std::endl;

// emcc stop exception
#define AVOID_EXCEPTION_TEST

using namespace mcl;

struct V {
	int n;
	unsigned int p[16];
};

CYBOZU_TEST_AUTO(addSub)
{
	static const struct {
		V a;
		V b;
		V c;
	} tbl[] = {
		{
			{ 1, { 123, } },
			{ 1, { 456, } },
			{ 1, { 579, } },
		},
		{
			{ 1, { 0xffffffff, } },
			{ 1, { 3, } },
			{ 2, { 2, 1 } },
		},
		{
			{ 3, { 0xffffffff, 1,          0xffffffff   } },
			{ 2, { 1,          0xfffffffe,              } },
			{ 4, { 0,          0,          0,         1 } },
		},
		{
			{ 3, { 0xffffffff, 5,          0xffffffff   } },
			{ 2, { 1,          0xfffffffe,              } },
			{ 4, { 0,          4,          0,         1 } },
		},
		{
			{ 3, { 0xffffffff, 5,          0xffffffff } },
			{ 1, { 1, } },
			{ 3, { 0,          6,          0xffffffff } },
		},
		{
			{ 3, { 1,          0xffffffff, 1 } },
			{ 3, { 0xffffffff, 0,          1 } },
			{ 3, { 0,          0,         3 } },
		},
		{
			{ 1, { 1 } },
			{ 3, { 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 4, { 0, 0, 0, 1 } },
		},
		{
			{ 1, { 0xffffffff } },
			{ 1, { 0xffffffff } },
			{ 2, { 0xfffffffe, 1 } },
		},
		{
			{ 2, { 0xffffffff, 0xffffffff } },
			{ 2, { 0xffffffff, 0xffffffff } },
			{ 3, { 0xfffffffe, 0xffffffff, 1 } },
		},
		{
			{ 3, { 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 3, { 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 4, { 0xfffffffe, 0xffffffff, 0xffffffff, 1 } },
		},
		{
			{ 4, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 4, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 5, { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
		},
		{
			{ 5, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 5, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 6, { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
		},
		{
			{ 6, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 6, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 7, { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
		},
		{
			{ 7, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 8, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 8, { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
		},
		{
			{ 8, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 8, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 9, { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
		},
		{
			{ 9, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 9, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{10, { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
		},
		{
			{10, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{10, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{11, { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
		},
		{
			{11, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{11, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{12, { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
		},
		{
			{12, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{12, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{13, { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
		},
		{
			{13, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{13, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{14, { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
		},
	};
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		Vint x, y, z, t;
		x.setArray(tbl[i].a.p, tbl[i].a.n);
		y.setArray(tbl[i].b.p, tbl[i].b.n);
		z.setArray(tbl[i].c.p, tbl[i].c.n);
		Vint::add(t, x, y);
		CYBOZU_TEST_EQUAL(t, z);

		Vint::add(t, y, x);
		CYBOZU_TEST_EQUAL(t, z);

		Vint::sub(t, z, x);
		CYBOZU_TEST_EQUAL(t, y);
	}
	{
		const uint32_t in[] = { 0xffffffff, 0xffffffff };
		const uint32_t out[] = { 0xfffffffe, 0xffffffff, 1 };
		Vint x, y;
		x.setArray(in, 2);
		y.setArray(out, 3);
		Vint::add(x, x, x);
		CYBOZU_TEST_EQUAL(x, y);
		Vint::sub(x, x, x);
		y.clear();
		CYBOZU_TEST_EQUAL(x, y);
	}
	{
		const uint32_t t0[] = {1, 2};
		const uint32_t t1[] = {3, 4, 5};
		const uint32_t t2[] = {4, 6, 5};
		Vint x, y, z;
		z.setArray(t2, 3);

		x.setArray(t0, 2);
		y.setArray(t1, 3);
		Vint::add(x, x, y);
		CYBOZU_TEST_EQUAL(x, z);

		x.setArray(t0, 2);
		y.setArray(t1, 3);
		Vint::add(x, y, x);
		CYBOZU_TEST_EQUAL(x, z);

		x.setArray(t0, 2);
		y.setArray(t1, 3);
		Vint::add(y, x, y);
		CYBOZU_TEST_EQUAL(y, z);

		x.setArray(t0, 2);
		y.setArray(t1, 3);
		Vint::add(y, y, x);
		CYBOZU_TEST_EQUAL(y, z);
	}
}

CYBOZU_TEST_AUTO(mul1)
{
	static const struct {
		V a;
		unsigned int b;
		V c;
	} tbl[] = {
		{
			{ 1, { 12, } },
			5,
			{ 1, { 60, } },
		},
		{
			{ 1, { 1234567, } },
			1,
			{ 1, { 1234567, } },
		},
		{
			{ 1, { 1234567, } },
			89012345,
			{ 2, { 0x27F6EDCF, 0x63F2, } },
		},
		{
			{ 3, { 0xffffffff, 0xffffffff, 0xffffffff, } },
			0x7fffffff,
			{ 4, { 0x80000001, 0xffffffff, 0xffffffff, 0x7ffffffe } },
		},
		{
			{ 3, { 0xffffffff, 0xffffffff, 0xffffffff, } },
			1,
			{ 3, { 0xffffffff, 0xffffffff, 0xffffffff, } },
		},
		{
			{ 2, { 0xffffffff, 1 } },
			0x7fffffff,
			{ 2, { 0x80000001, 0xfffffffd } },
		},
	};
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		Vint x, z, t;
		unsigned int y;
		x.setArray(tbl[i].a.p, tbl[i].a.n);
		y = tbl[i].b;
		z.setArray(tbl[i].c.p, tbl[i].c.n);
		Vint::mul(t, x, y);
		CYBOZU_TEST_EQUAL(t, z);

		Vint::mul(x, x, y);
		CYBOZU_TEST_EQUAL(x, z);
	}
}

CYBOZU_TEST_AUTO(mul2)
{
	static const struct {
		V a;
		V b;
		V c;
	} tbl[] = {
		{
			{ 1, { 12, } },
			{ 1, { 5, } },
			{ 1, { 60, } },
		},
		{
			{ 1, { 1234567, } },
			{ 1, { 89012345, } },
			{ 2, { 0x27F6EDCF, 0x63F2, } },
		},
		{
			{ 3, { 0xffffffff, 0xffffffff, 0xffffffff, } },
			{ 1, { 0xffffffff, } },
			{ 4, { 0x00000001, 0xffffffff, 0xffffffff, 0xfffffffe } },
		},
		{
			{ 2, { 0xffffffff, 1 } },
			{ 1, { 0xffffffff, } },
			{ 3, { 0x00000001, 0xfffffffd, 1 } },
		},
		{
			{ 2, { 0xffffffff, 1 } },
			{ 1, { 0xffffffff, } },
			{ 3, { 0x00000001, 0xfffffffd, 1 } },
		},
		{
			{ 2, { 1, 1 } },
			{ 2, { 1, 1 } },
			{ 3, { 1, 2, 1 } },
		},
		{
			{ 3, { 0xffffffff, 0xffffffff, 1 } },
			{ 2, { 0xffffffff, 0xffffffff } },
			{ 5, { 1, 0, 0xfffffffd, 0xffffffff, 1 } },
		},
	};
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		Vint x, y, z, t;
		x.setArray(tbl[i].a.p, tbl[i].a.n);
		y.setArray(tbl[i].b.p, tbl[i].b.n);
		z.setArray(tbl[i].c.p, tbl[i].c.n);
		Vint::mul(t, x, y);
		CYBOZU_TEST_EQUAL(t, z);

		Vint::mul(t, y, x);
		CYBOZU_TEST_EQUAL(t, z);
	}
	{
		const uint32_t in[] = { 0xffffffff, 1 };
		const uint32_t out[] = { 1, 0xfffffffc, 3 };
		Vint x, y, z;
		y.setArray(out, 3);
		x.setArray(in, 2);
		z = x;
		Vint::mul(x, x, x);
		CYBOZU_TEST_EQUAL(x, y);

		x.setArray(in, 2);
		Vint::mul(x, x, z);
		CYBOZU_TEST_EQUAL(x, y);

		x.setArray(in, 2);
		Vint::mul(x, z, x);
		CYBOZU_TEST_EQUAL(x, y);

		x.setArray(in, 2);
		Vint::mul(x, z, z);
		CYBOZU_TEST_EQUAL(x, y);
	}
	{
		Vint a("285434247217355341057");
		a *= a;
		CYBOZU_TEST_EQUAL(a, Vint("81472709484538325259309302444004789877249"));
	}
}

CYBOZU_TEST_AUTO(div1)
{
	static const struct {
		V a;
		unsigned int b;
		unsigned int r;
		V c;
	} tbl[] = {
		{
			{ 1, { 100, } },
			1, 0,
			{ 1, { 100, } },
		},
		{
			{ 1, { 100, } },
			100, 0,
			{ 1, { 1, } },
		},
		{
			{ 1, { 100, } },
			101, 100,
			{ 1, { 0, } },
		},
		{
			{ 1, { 100, } },
			2, 0,
			{ 1, { 50, } },
		},
		{
			{ 1, { 100, } },
			3, 1,
			{ 1, { 33, } },
		},
		{
			{ 2, { 0xffffffff, 0xffffffff } },
			1, 0,
			{ 2, { 0xffffffff, 0xffffffff, } },
		},
		{
			{ 2, { 0xffffffff, 0xffffffff } },
			123, 15,
			{ 2, { 0x4d0214d0, 0x214d021 } },
		},
	};
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		Vint x, z, t;
		unsigned int b, r, u;
		x.setArray(tbl[i].a.p, tbl[i].a.n);
		b = tbl[i].b;
		r = tbl[i].r;
		z.setArray(tbl[i].c.p, tbl[i].c.n);

		u = (unsigned int)Vint::divMods1(&t, x, b);
		CYBOZU_TEST_EQUAL(t, z);
		CYBOZU_TEST_EQUAL(u, r);

		u = (unsigned int)Vint::divMods1(&x, x, b);
		CYBOZU_TEST_EQUAL(x, z);
		CYBOZU_TEST_EQUAL(u, r);
	}
}

CYBOZU_TEST_AUTO(div2)
{
	static const struct {
		V x;
		V y;
		V q;
		V r;
	} tbl[] = {
		{
			{ 1, { 100 } },
			{ 1, { 3 } },
			{ 1, { 33 } },
			{ 1, { 1 } },
		},
		{
			{ 2, { 1, 1 } },
			{ 2, { 0, 1 } },
			{ 1, { 1 } },
			{ 1, { 1 } },
		},
		{
			{ 2, { 0xffffffff, 0xffffffff } },
			{ 2, { 0, 1 } },
			{ 1, { 0xffffffff } },
			{ 1, { 0xffffffff } },
		},
		{
			{ 2, { 0xffffffff, 0xffffffff } },
			{ 2, { 0xffffffff, 1 } },
			{ 1, { 0x80000000 } },
			{ 1, { 0x7fffffff } },
		},
		{
			{ 3, { 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 2, { 0xffffffff, 1 } },
			{ 2, { 0x40000000, 0x80000000 } },
			{ 1, { 0x3fffffff } },
		},
		{
			{ 4, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 3, { 1, 0, 1 } },
			{ 2, { 0xffffffff, 0xffffffff } },
			{ 1, { 0 } },
		},
		{
			{ 4, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 3, { 1, 0xffffffff, 0xffffffff } },
			{ 2, { 0, 1 } },
			{ 2, { 0xffffffff, 0xfffffffe } },
		},
		{
			{ 4, { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff } },
			{ 3, { 1, 0, 0xffffffff } },
			{ 2, { 1, 1 } },
			{ 2, { 0xfffffffe, 0xfffffffe } },
		},
		{
			{ 4, { 0xffffffff, 0xffffffff, 0xffffffff, 1 } },
			{ 3, { 1, 0, 0xffffffff } },
			{ 1, { 2 } },
			{ 3, { 0xfffffffd, 0xffffffff, 1 } },
		},
		{
			{ 4, { 0, 0, 1, 1 } },
			{ 2, { 1, 1 } },
			{ 3, { 0, 0, 1 } },
			{ 1, { 0 } },
		},
		{
			{ 3, { 5, 5, 1} },
			{ 2, { 1, 2 } },
			{ 1, { 0x80000002 } },
			{ 1, { 0x80000003, } },
		},
		{
			{ 2, { 5, 5} },
			{ 2, { 1, 1 } },
			{ 1, { 5 } },
			{ 1, { 0, } },
		},
		{
			{ 2, { 5, 5} },
			{ 2, { 2, 1 } },
			{ 1, { 4 } },
			{ 1, { 0xfffffffd, } },
		},
		{
			{ 3, { 5, 0, 5} },
			{ 3, { 2, 0, 1 } },
			{ 1, { 4 } },
			{ 2, { 0xfffffffd, 0xffffffff } },
		},
		{
			{ 2, { 4, 5 } },
			{ 2, { 5, 5 } },
			{ 1, { 0 } },
			{ 2, { 4, 5 } },
		},
		{
			{ 1, { 123 } },
			{ 2, { 1, 1 } },
			{ 1, { 0 } },
			{ 1, { 123 } },
		},
		{
			{ 1, { 123 } },
			{ 3, { 1, 1, 1 } },
			{ 1, { 0 } },
			{ 1, { 123 } },
		},
	};
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		Vint x, y, q, r;
		x.setArray(tbl[i].x.p, tbl[i].x.n);
		y.setArray(tbl[i].y.p, tbl[i].y.n);
		q.setArray(tbl[i].q.p, tbl[i].q.n);
		r.setArray(tbl[i].r.p, tbl[i].r.n);

		Vint qt, rt;
		Vint::quotRem(&qt, rt, x, y);
		CYBOZU_TEST_EQUAL(qt, q);
		CYBOZU_TEST_EQUAL(rt, r);

		Vint::mul(y, y, qt);
		Vint::add(y, y, rt);
		CYBOZU_TEST_EQUAL(x, y);

		x.setArray(tbl[i].x.p, tbl[i].x.n);
		y.setArray(tbl[i].y.p, tbl[i].y.n);
		Vint::quotRem(&x, rt, x, y);
		CYBOZU_TEST_EQUAL(x, q);
		CYBOZU_TEST_EQUAL(rt, r);

		x.setArray(tbl[i].x.p, tbl[i].x.n);
		y.setArray(tbl[i].y.p, tbl[i].y.n);
		Vint::quotRem(&y, rt, x, y);
		CYBOZU_TEST_EQUAL(y, q);
		CYBOZU_TEST_EQUAL(rt, r);

		x.setArray(tbl[i].x.p, tbl[i].x.n);
		y.setArray(tbl[i].y.p, tbl[i].y.n);
		Vint::quotRem(&x, y, x, y);
		CYBOZU_TEST_EQUAL(x, q);
		CYBOZU_TEST_EQUAL(y, r);

		x.setArray(tbl[i].x.p, tbl[i].x.n);
		y.setArray(tbl[i].y.p, tbl[i].y.n);
		Vint::quotRem(&y, x, x, y);
		CYBOZU_TEST_EQUAL(y, q);
		CYBOZU_TEST_EQUAL(x, r);
	}
	{
		const uint32_t in[] = { 1, 1 };
		Vint x, y, z;
		x.setArray(in, 2);
		Vint::quotRem(&x, y, x, x);
		z = 1;
		CYBOZU_TEST_EQUAL(x, z);
		z.clear();
		CYBOZU_TEST_EQUAL(y, z);

		Vint::quotRem(&y, x, x, x);
		z = 1;
		CYBOZU_TEST_EQUAL(y, z);
		z.clear();
		CYBOZU_TEST_EQUAL(x, z);
	}
}

CYBOZU_TEST_AUTO(quotRem)
{
	const struct {
		const char *x;
		const char *y;
		const char *r;
	} tbl[] = {
		{
			"1448106640508192452750709206294683535529268965445799785581837640324321797831381715960812126274894517677713278300997728292641936248881345120394299128611830",
			"82434016654300679721217353503190038836571781811386228921167322412819029493183",
			"72416512377294697540770834088766459385112079195086911762075702918882982361282"
		},
		{
			"97086308670107713719105336221824613370040805954034005192338040686500414395543303807941158656814978071549225072789349941064484974666540443679601226744652",
			"82434016654300679721217353503190038836571781811386228921167322412819029493183",
			"41854959563040430269871677548536437787164514279279911478858426970427834388586",
		},
		{
			"726838724295606887174238120788791626017347752989142414466410919788841485181240131619880050064495352797213258935807786970844241989010252",
			"82434016654300679721217353503190038836571781811386228921167322412819029493183",
			"81378967132566843036693176764684783485107373533583677681931133755003929106966",
		},
		{
			"85319207237201203511459960875801690195851794174784746933408178697267695525099750",
			"82434016654300679721217353503190038836571781811386228921167322412819029493183",
			"82434016654300679721217353503190038836571781811386228921167322412819029148528",
		},
		{
			"0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
			"0x100000000000000000000000000000000000000000000000001",
			"1606938044258990275541962092341162602522202993782724115824640",
		},
		{
			"0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
			"0x1000000000000000000000000000000000000000000000000000000000000000000000000000000001",
			"34175792574734561318320347298712833833643272357332299899995954578095372295314880347335474659983360",
		},
		{
			"0xfffffffffffff000000000000000000000000000000000000000000000000000000000000000000",
			"0x100000000000000000000000000000000000000000000000000000000000000000001",
			"7558907585412001237250713901367146624661464598973016020495791084036551510708977665",
		},
		{
			"0xfffffffffffff000000000000000000000000000000000000000000000000000000000000000000",
			"0xfffffffffffff0000000000000000000000000000000000000000000000000000000000000001",
			"521481209941628322292632858916605385658190900090571826892867289394157573281830188869820088065",
		},
	};
	mcl::Vint x, y, r;
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		x.setStr(tbl[i].x);
		y.setStr(tbl[i].y);
		r.setStr(tbl[i].r);
		x %= y;
		CYBOZU_TEST_EQUAL(x, r);
	}
}

CYBOZU_TEST_AUTO(string)
{
	const struct {
		uint32_t v[5];
		size_t vn;
		const char *str;
		const char *hex;
		const char *bin;
	} tbl[] = {
		{ { 0 }, 0, "0", "0x0", "0b0" },
		{ { 12345 }, 1, "12345", "0x3039", "0b11000000111001" },
		{ { 0xffffffff }, 1, "4294967295", "0xffffffff", "0b11111111111111111111111111111111" },
		{ { 0, 1 }, 2, "4294967296", "0x100000000", "0b100000000000000000000000000000000" },
		{ { 0, 0, 0, 0, 1 }, 5, "340282366920938463463374607431768211456", "0x100000000000000000000000000000000", "0b100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" },
	};
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		Vint x, y;
		x.setArray(tbl[i].v,tbl[i].vn);
		CYBOZU_TEST_EQUAL(x.getStr(10), tbl[i].str);
		y.setStr(tbl[i].str);
		CYBOZU_TEST_EQUAL(x, y);
		x = 1;
		x.setStr(tbl[i].hex);
		CYBOZU_TEST_EQUAL(x, y);
	}
}

CYBOZU_TEST_AUTO(shift)
{
	Vint x("123423424918471928374192874198274981274918274918274918243");
	Vint y, z;

	const size_t unitBitSize = Vint::unitBitSize;
	Vint s;
	// shl
	for (size_t i = 1; i < 31; i++) {
		Vint::shl(y, x, i);
		z = x * (Vint::Unit(1) << i);
		CYBOZU_TEST_EQUAL(y, z);
		y = x << i;
		CYBOZU_TEST_EQUAL(y, z);
		y = x;
		y <<= i;
		CYBOZU_TEST_EQUAL(y, z);
	}
	for (int i = 0; i < 4; i++) {
		Vint::shl(y, x, i * unitBitSize);
		Vint::pow(s, Vint(2), i * unitBitSize);
		z = x * s;
		CYBOZU_TEST_EQUAL(y, z);
		y = x << (i * unitBitSize);
		CYBOZU_TEST_EQUAL(y, z);
		y = x;
		y <<= (i * unitBitSize);
		CYBOZU_TEST_EQUAL(y, z);
	}
	for (int i = 0; i < 100; i++) {
		y = x << i;
		Vint::pow(s, Vint(2), i);
		z = x * s;
		CYBOZU_TEST_EQUAL(y, z);
		y = x;
		y <<= i;
		CYBOZU_TEST_EQUAL(y, z);
	}

	// shr
	for (size_t i = 1; i < 31; i++) {
		Vint::shr(y, x, i);
		z = x / (Vint::Unit(1) << i);
		CYBOZU_TEST_EQUAL(y, z);
		y = x >> i;
		CYBOZU_TEST_EQUAL(y, z);
		y = x;
		y >>= i;
		CYBOZU_TEST_EQUAL(y, z);
	}
	for (int i = 0; i < 3; i++) {
		Vint::shr(y, x, i * unitBitSize);
		Vint::pow(s, Vint(2), i * unitBitSize);
		z = x / s;
		CYBOZU_TEST_EQUAL(y, z);
		y = x >> (i * unitBitSize);
		CYBOZU_TEST_EQUAL(y, z);
		y = x;
		y >>= (i * unitBitSize);
		CYBOZU_TEST_EQUAL(y, z);
	}
	for (int i = 0; i < 100; i++) {
		y = x >> i;
		Vint::pow(s, Vint(2), i);
		z = x / s;
		CYBOZU_TEST_EQUAL(y, z);
		y = x;
		y >>= i;
		CYBOZU_TEST_EQUAL(y, z);
	}
	{
		Vint a = 0, zero = 0;
		a <<= Vint::unitBitSize;
		CYBOZU_TEST_EQUAL(a, zero);
	}
}

CYBOZU_TEST_AUTO(getBitSize)
{
	{
		Vint zero = 0;
		CYBOZU_TEST_EQUAL(zero.getBitSize(), 1);
		zero <<= (Vint::unitBitSize - 1);
		CYBOZU_TEST_EQUAL(zero.getBitSize(), 1);
		zero <<= Vint::unitBitSize;
		CYBOZU_TEST_EQUAL(zero.getBitSize(), 1);
	}

	{
		Vint a = 1;
		CYBOZU_TEST_EQUAL(a.getBitSize(), 1);
		a = 2;
		CYBOZU_TEST_EQUAL(a.getBitSize(), 2);
		a = 3;
		CYBOZU_TEST_EQUAL(a.getBitSize(), 2);
		a = 4;
		CYBOZU_TEST_EQUAL(a.getBitSize(), 3);
	}

	{
		Vint a = 5;
		const size_t msbindex = a.getBitSize();
		const size_t width = 100;
		const size_t time = 3;
		for (size_t i = 0; i < time; ++i) {
			a <<= width;
			CYBOZU_TEST_EQUAL(a.getBitSize(), msbindex + width*(i + 1));
		}

		for (size_t i = 0; i < time*2; ++i) {
			a >>= width/2;
			CYBOZU_TEST_EQUAL(a.getBitSize(), msbindex + width*time - (width/2)*(i + 1));
		}
		a >>= width;
		CYBOZU_TEST_ASSERT(a.isZero());
		CYBOZU_TEST_EQUAL(a.getBitSize(), 1);
	}

	{
		Vint b("12"), c("345"), d("67890");
		size_t bl = b.getBitSize(), cl = c.getBitSize(), dl = d.getBitSize();
		CYBOZU_TEST_ASSERT((b*c).getBitSize()   <= bl + cl);
		CYBOZU_TEST_ASSERT((c*d).getBitSize()   <= cl + dl);
		CYBOZU_TEST_ASSERT((b*c*d).getBitSize() <= bl + cl + dl);
	}
}

CYBOZU_TEST_AUTO(bit)
{
	Vint a;
	a.setStr("0x1234567890abcdef");
	bool tvec[] = {
		1,1,1,1,0  ,1,1,1,1,0
		,1,1,0,0,1 ,1,1,1,0,1
		,0,1,0,1,0 ,0,0,0,1,0
		,0,1,0,0,0 ,1,1,1,1,0
		,0,1,1,0,1 ,0,1,0,0,0
		,1,0,1,1,0 ,0,0,1,0,0
		,1
	};
	CYBOZU_TEST_EQUAL(a.getBitSize(), sizeof(tvec)/sizeof(*tvec));
	for (int i = (int)a.getBitSize() - 1; i >= 0; --i) {
		CYBOZU_TEST_EQUAL(a.testBit(i), tvec[i]);
	}
}

CYBOZU_TEST_AUTO(sample)
{
	using namespace mcl;
	Vint x(1);
	Vint y("123456789");
	Vint z;

	x = 1;	// set by int
	y.setStr("123456789"); // set by decimal
	z.setStr("0xffffffff"); // set by hex
	x += z;

	x = 2;
	y = 250;
	Vint::pow(x, x, y);
	Vint r, q;
	r = x % y;
	q = x / y;
	CYBOZU_TEST_EQUAL(q * y + r, x);

	Vint::quotRem(&q, r, x, y); // get both r and q
	CYBOZU_TEST_EQUAL(q * y + r, x);
}

CYBOZU_TEST_AUTO(Vint)
{
	const struct {
		int a;
		int b;
		/*
			q, r ; like C
			q2, r2 ; like Python
		*/
		int add, sub, mul, q, r, q2, r2;
	} tbl[] = {
		{  13,  5,  18,   8,  65,  2,  3,  2,  3 },
		{  13, -5,   8,  18, -65, -2,  3, -3, -2 },
		{ -13,  5,  -8, -18, -65, -2, -3, -3,  2 },
		{ -13, -5, -18,  -8,  65,  2, -3,  2, -3 },
		{  5,  13,  18,  -8,  65, 0,  5 ,  0,  5},
		{  5, -13,  -8,  18, -65, 0,  5 , -1, -8},
		{ -5,  13,   8, -18, -65, 0, -5 , -1,  8},
		{ -5, -13, -18,   8,  65, 0, -5 ,  0, -5},
	};
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		Vint a = tbl[i].a;
		Vint b = tbl[i].b;
		Vint add = a + b;
		Vint sub = a - b;
		Vint mul = a * b;
		Vint q = a / b;
		Vint r = a % b;
		Vint q2, r2;
		Vint::quotRem(&q2, r2, a, b);
		CYBOZU_TEST_EQUAL(add, tbl[i].add);
		CYBOZU_TEST_EQUAL(sub, tbl[i].sub);
		CYBOZU_TEST_EQUAL(mul, tbl[i].mul);
		CYBOZU_TEST_EQUAL(q, tbl[i].q);
		CYBOZU_TEST_EQUAL(r, tbl[i].r);
		CYBOZU_TEST_EQUAL(q * b + r, a);
		CYBOZU_TEST_EQUAL(q2, tbl[i].q2);
		CYBOZU_TEST_EQUAL(r2, tbl[i].r2);
		CYBOZU_TEST_EQUAL(q2 * b + r2, a);
	}
	CYBOZU_TEST_EQUAL(Vint("15") / Vint("3"), Vint("5"));
	CYBOZU_TEST_EQUAL(Vint("15") / Vint("-3"), Vint("-5"));
	CYBOZU_TEST_EQUAL(Vint("-15") / Vint("3"), Vint("-5"));
	CYBOZU_TEST_EQUAL(Vint("-15") / Vint("-3"), Vint("5"));

	CYBOZU_TEST_EQUAL(Vint("15") % Vint("3"), Vint("0"));
	CYBOZU_TEST_EQUAL(Vint("15") % Vint("-3"), Vint("0"));
	CYBOZU_TEST_EQUAL(Vint("-15") % Vint("3"), Vint("0"));
	CYBOZU_TEST_EQUAL(Vint("-15") % Vint("-3"), Vint("0"));

	CYBOZU_TEST_EQUAL(Vint("-0") + Vint("-3"), Vint("-3"));
	CYBOZU_TEST_EQUAL(Vint("-0") - Vint("-3"), Vint("3"));
	CYBOZU_TEST_EQUAL(Vint("-3") + Vint("-0"), Vint("-3"));
	CYBOZU_TEST_EQUAL(Vint("-3") - Vint("-0"), Vint("-3"));

	CYBOZU_TEST_EQUAL(Vint("-0") + Vint("3"), Vint("3"));
	CYBOZU_TEST_EQUAL(Vint("-0") - Vint("3"), Vint("-3"));
	CYBOZU_TEST_EQUAL(Vint("3") + Vint("-0"), Vint("3"));
	CYBOZU_TEST_EQUAL(Vint("3") - Vint("-0"), Vint("3"));

	CYBOZU_TEST_EQUAL(Vint("0"), Vint("0"));
	CYBOZU_TEST_EQUAL(Vint("0"), Vint("-0"));
	CYBOZU_TEST_EQUAL(Vint("-0"), Vint("0"));
	CYBOZU_TEST_EQUAL(Vint("-0"), Vint("-0"));

	CYBOZU_TEST_ASSERT(Vint("2") < Vint("3"));
	CYBOZU_TEST_ASSERT(Vint("-2") < Vint("3"));
	CYBOZU_TEST_ASSERT(Vint("-5") < Vint("-3"));
	CYBOZU_TEST_ASSERT(Vint("-0") < Vint("1"));
	CYBOZU_TEST_ASSERT(Vint("-1") < Vint("-0"));

	CYBOZU_TEST_ASSERT(Vint("5") > Vint("3"));
	CYBOZU_TEST_ASSERT(Vint("5") > Vint("-3"));
	CYBOZU_TEST_ASSERT(Vint("-2") > Vint("-3"));
	CYBOZU_TEST_ASSERT(Vint("3") > Vint("-0"));
	CYBOZU_TEST_ASSERT(Vint("-0") > Vint("-1"));

	{
		const struct {
			const char *str;
			int s;
			int shl;
			int shr;
		} tbl2[] = {
			{ "0", 1, 0, 0 },
			{ "-0", 1, 0, 0 },
			{ "1", 1, 2, 0 },
			{ "-1", 1, -2, 0 },
			{ "12345", 3, 98760, 1543 },
			{ "-12345", 3, -98760, 0 },
		};
		for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl2); i++) {
			Vint a = Vint(tbl2[i].str);
			Vint shl = a << tbl2[i].s;
			CYBOZU_TEST_EQUAL(shl, tbl2[i].shl);
			if (!a.isNegative()) {
				Vint shr = a >> tbl2[i].s;
				CYBOZU_TEST_EQUAL(shr, tbl2[i].shr);
			}
		}
	}
}

CYBOZU_TEST_AUTO(add2)
{
	Vint x, y, z, w;
	x.setStr("2416089439321382744001761632872637936198961520379024187947524965775137204955564426500438089001375107581766516460437532995850581062940399321788596606850");
	y.setStr("2416089439321382743300544243711595219403446085161565705825288050160594425031420687263897209379984490503106207071010949258995096347962762372787916800000");
	z.setStr("701217389161042716795515435217458482122236915614542779924143739236540879621390617078660309389426583736855484714977636949000679806850");
	Vint::sub(w, x, y);
	CYBOZU_TEST_EQUAL(w, z);

	Vint a, c, d;

	a.setStr("-2416089439321382744001761632872637936198961520379024187947524965775137204955564426500438089001375107581766516460437532995850581062940399321788596606850");
	c.setStr("2416089439321382743300544243711595219403446085161565705825288050160594425031420687263897209379984490503106207071010949258995096347962762372787916800000");
	a = a + c;

	d.setStr("-701217389161042716795515435217458482122236915614542779924143739236540879621390617078660309389426583736855484714977636949000679806850");
	CYBOZU_TEST_EQUAL(a, d);
}

CYBOZU_TEST_AUTO(stream)
{
	{
		Vint x, y, z, w;
		x.setStr("12345678901232342424242423423429922");
		y.setStr("23423423452424242343");
		std::ostringstream oss;
		oss << x << ' ' << y;
		std::istringstream iss(oss.str());
		iss >> z >> w;
		CYBOZU_TEST_EQUAL(x, z);
		CYBOZU_TEST_EQUAL(y, w);
	}
	{
		Vint x, y, z, w;
		x.setStr("0x100");
		y.setStr("123");
		std::ostringstream oss;
		oss << x << ' ' << y;
		std::istringstream iss(oss.str());
		iss >> z >> w;
		CYBOZU_TEST_EQUAL(x, z);
		CYBOZU_TEST_EQUAL(y, w);
	}
	{
		Vint x, y, z, w;
		x.setStr("12345678901232342424242423423429922");
		y.setStr("-23423423452424242343");
		std::ostringstream oss;
		oss << x << ' ' << y;
		std::istringstream iss(oss.str());
		iss >> z >> w;
		CYBOZU_TEST_EQUAL(x, z);
		CYBOZU_TEST_EQUAL(y, w);
	}
}

CYBOZU_TEST_AUTO(inc_dec)
{
	Vint x = 3;
	CYBOZU_TEST_EQUAL(x++, 3);
	CYBOZU_TEST_EQUAL(x, 4);
	CYBOZU_TEST_EQUAL(++x, 5);
	CYBOZU_TEST_EQUAL(x, 5);

	CYBOZU_TEST_EQUAL(x--, 5);
	CYBOZU_TEST_EQUAL(x, 4);
	CYBOZU_TEST_EQUAL(--x, 3);
	CYBOZU_TEST_EQUAL(x, 3);
}

CYBOZU_TEST_AUTO(withInt)
{
	Vint x = 15;
	x += 3;
	CYBOZU_TEST_EQUAL(x, 18);
	x -= 2;
	CYBOZU_TEST_EQUAL(x, 16);
	x *= 2;
	CYBOZU_TEST_EQUAL(x, 32);
	x /= 3;
	CYBOZU_TEST_EQUAL(x, 10);
	x = -x;
	CYBOZU_TEST_EQUAL(x, -10);
	x += 1;
	CYBOZU_TEST_EQUAL(x, -9);
	x -= 2;
	CYBOZU_TEST_EQUAL(x, -11);
	x *= 2;
	CYBOZU_TEST_EQUAL(x, -22);
	x /= 5;
	CYBOZU_TEST_EQUAL(x, -4);
	x = -22;
	x %= 5;
	CYBOZU_TEST_EQUAL(x, -2);

	x = 3;
	x += -2;
	CYBOZU_TEST_EQUAL(x, 1);
	x += -5;
	CYBOZU_TEST_EQUAL(x, -4);
	x -= -7;
	CYBOZU_TEST_EQUAL(x, 3);
	x *= -1;
	CYBOZU_TEST_EQUAL(x, -3);
	x /= -1;
	CYBOZU_TEST_EQUAL(x, 3);
}

CYBOZU_TEST_AUTO(pow)
{
	Vint x = 2;
	Vint y;
	Vint::pow(y, x, 3);
	CYBOZU_TEST_EQUAL(y, 8);
	x = -2;
	Vint::pow(y, x, 3);
	CYBOZU_TEST_EQUAL(y, -8);
#ifndef AVOID_EXCEPTION_TEST
	CYBOZU_TEST_EXCEPTION(Vint::pow(y, x, -2), std::exception);
#endif
}

CYBOZU_TEST_AUTO(powMod)
{
	Vint x = 7;
	Vint m = 65537;
	Vint y;
	Vint::powMod(y, x, 20, m);
	CYBOZU_TEST_EQUAL(y, 55277);
	Vint::powMod(y, x, m - 1, m);
	CYBOZU_TEST_EQUAL(y, 1);
}

CYBOZU_TEST_AUTO(andOr)
{
	Vint x("1223480928420984209849242");
	Vint y("29348220482094820948208420984209482048204289482");
	Vint z;
	z = x & y;
	CYBOZU_TEST_EQUAL(z, Vint("1209221003550923564822922"));
	z = x | y;
	CYBOZU_TEST_EQUAL(z, Vint("29348220482094820948208435244134352108849315802"));
#ifndef AVOID_EXCEPTION_TEST
	CYBOZU_TEST_EXCEPTION(Vint("-2") | Vint("5"), std::exception);
	CYBOZU_TEST_EXCEPTION(Vint("-2") & Vint("5"), std::exception);
#endif
	x = 8;
	x |= 7;
	CYBOZU_TEST_EQUAL(x, 15);
	x = 65536;
	y = 8;
	y &= x;
	CYBOZU_TEST_EQUAL(y, 0);
}

CYBOZU_TEST_AUTO(invMod)
{
	Vint m("100000000000000000039");
	for (int i = 1; i < 100; i++) {
		Vint x = i;
		Vint y;
		Vint::invMod(y, x, m);
		CYBOZU_TEST_EQUAL((y * x) % m, 1);
	}
}

CYBOZU_TEST_AUTO(isPrime)
{
	int primeTbl[] = {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
		67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
		139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,197, 199, 211,
		223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
		293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
		383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
		463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563,
		569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643,
		647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739,
		743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829,
		839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
		941, 947, 953, 967, 971, 977, 983, 991, 997
	};
	typedef std::set<int> IntSet;
	IntSet primes;
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(primeTbl); i++) {
		primes.insert(primeTbl[i]);
	}
	for (int i = 0; i < 1000; i++) {
		bool ok = primes.find(i) != primes.end();
		bool my = Vint(i).isPrime();
		CYBOZU_TEST_EQUAL(ok, my);
	}
	const struct {
		const char *n;
		bool isPrime;
	} tbl[] = {
		{ "65537", true },
		{ "449065", false },
		{ "488881", false },
		{ "512461", false },
		{ "18446744073709551629", true },
		{ "18446744073709551631", false },
		{ "0x10000000000000000000000000000000000000007", true },
		{ "0x10000000000000000000000000000000000000009", false },
		{ "0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f", true },
		{ "0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2d", false },
	};
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		Vint x(tbl[i].n);
		CYBOZU_TEST_EQUAL(x.isPrime(), tbl[i].isPrime);
	}
}

CYBOZU_TEST_AUTO(gcd)
{
	Vint x = 12;
	Vint y = 18;
	Vint z;
	Vint::gcd(z, x, y);
	CYBOZU_TEST_EQUAL(z, 6);
	Vint::lcm(z, x, y);
	CYBOZU_TEST_EQUAL(z, 36);
	Vint::lcm(x, x, y);
	CYBOZU_TEST_EQUAL(x, 36);
	Vint::lcm(x, x, x);
	CYBOZU_TEST_EQUAL(x, 36);
}

CYBOZU_TEST_AUTO(jacobi)
{
	const struct {
		const char *m;
		const char *n;
		int ok;
	} tbl[] = {
		{ "0", "1", 1 },
		{ "1", "1", 1 },
		{ "123", "1", 1 },
		{ "45", "77", -1 },
		{ "60", "121", 1 },
		{ "12345672342342342342428", "923423423424753211", 1 },
		{ "12345672342342342342428","34592342234235424753211", -1 },
	};
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		int my = Vint::jacobi(Vint(tbl[i].m), Vint(tbl[i].n));
		CYBOZU_TEST_EQUAL(my, tbl[i].ok);
	}
}

CYBOZU_TEST_AUTO(bench)
{
	Vint x, y, z;
	x.setStr("0x2523648240000001ba344d80000000086121000000000013a700000000000013");
	y.setStr("0x1802938109810498104982094820498203942804928049284092424902424243");

	int N = 100000;
	CYBOZU_BENCH_C("add", N, Vint::add, z, x, y);
	CYBOZU_BENCH_C("sub", N, Vint::sub, z, x, y);
	CYBOZU_BENCH_C("mul", N, Vint::mul, z, x, y);
	CYBOZU_BENCH_C("div", N, Vint::div, y, z, x);
}
