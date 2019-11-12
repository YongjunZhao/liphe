#ifndef __HELIB_KEYS__
#define __HELIB_KEYS__

#include <NTL/ZZ.h>
#include <FHE.h>
#include <EncryptedArray.h>
#include <stdlib.h>
#include <vector>

// FIXME: The size of primes in the chain should be computed at run-time
#if (NTL_SP_NBITS<44)
#define FHE_p2Size NTL_SP_NBITS
#else
#define FHE_p2Size 44
#endif
#define FHE_p2Bound (1L<<FHE_p2Size)
#define FHE_pSize (FHE_p2Size/2) /* The size of levels in the chain */


class HelibKeys {
private:
	FHEPubKey *_publicKey;
	FHESecKey *_secretKey;
	EncryptedArray *_ea;
	FHEcontext *_context;

	long _p;
	long _r;
public:
	HelibKeys() : _publicKey(NULL), _secretKey(NULL), _ea(NULL), _context(NULL), _p(0), _r(0) {}
	HelibKeys(const HelibKeys &h) : _publicKey(h._publicKey), _secretKey(h._secretKey), _ea(h._ea), _context(h._context), _p(h._p), _r(h._r) {}
	HelibKeys(FHEPubKey *pub, FHESecKey *sec, EncryptedArray *ea, FHEcontext *ctx) : _p(0), _r(0) { setKeys(pub, sec, ea, ctx); }

	void initKeys(long s, long R, long p, long r, long d, long c, long k, long w, long L, long m, const std::vector<long> &gens, const std::vector<long> &ords);
	void initKeys_with_recrypt(long s, long p, long r, long d, long c, long k, long w, long L, long m);
	void setKeys(FHEPubKey *pub, FHESecKey *sec, EncryptedArray *ea, FHEcontext *ctx)
		{ _publicKey = pub; _secretKey = sec; _ea = ea; _context = ctx; }

	long &p() { return _p; }
	long &r() { return _r; }

	int nslots() const { return _ea->size(); }
	int simd_factor() const { return nslots(); }

	FHEPubKey &publicKey() { return *_publicKey; }
	EncryptedArray &ea() { return *_ea; }
	Ctxt encrypt(int b);
	void encrypt(Ctxt &c, int b);
	long decrypt(const Ctxt &b);

	Ctxt encrypt(const std::vector<long> &b);
	Ctxt encrypt(const std::vector<int> &b);
	void encrypt(Ctxt &c, const std::vector<long> &b);
	void encrypt(Ctxt &c, const std::vector<int> &b);
	void decrypt(std::vector<long> &, const Ctxt &b);

	void write_to_file(std::ostream& s);
	void read_from_file(std::istream& s);

	void print(const Ctxt &b);

	void rotate(Ctxt &a, int step) { _ea->rotate(a, step); }
};

#endif
