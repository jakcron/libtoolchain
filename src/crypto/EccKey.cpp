#include <tc/crypto/EccKey.h>
#include <tc/crypto/EccUtil.h>
#include <tc/crypto/EccKeyGenerator.h>

tc::crypto::EccPublicKey::EccPublicKey(EccCurveType curve_type, const byte_t* Q, size_t Q_size)
{
	if (EccUtil::eccIntegerByteLength(curve_type) == 0) throw tc::ArgumentException("tc::crypto::EccPublicKey()", "curve_type was not supported/valid");

	if (Q != nullptr && Q_size != 0)
	{
		this->curve_type = curve_type;
		this->d = tc::ByteData();
		this->Q = tc::ByteData(Q, Q_size);
	}
}

tc::crypto::EccPrivateKey::EccPrivateKey(EccCurveType curve_type, const byte_t* d, size_t d_size, const byte_t* Q, size_t Q_size)
{
	if (EccUtil::eccIntegerByteLength(curve_type) == 0) throw tc::ArgumentException("tc::crypto::EccPublicKey()", "curve_type was not supported/valid");

	if (d != nullptr && d_size != 0 && Q != nullptr && Q_size != 0)
	{
		this->curve_type = curve_type;
		this->d = tc::ByteData(d, d_size);
		this->Q = tc::ByteData(Q, Q_size);
	}
}

tc::crypto::EccPrivateKey::EccPrivateKey(EccCurveType curve_type, const byte_t* d, size_t d_size)
{
	size_t ecc_int_byte_length = EccUtil::eccIntegerByteLength(curve_type);
	if (ecc_int_byte_length == 0) throw tc::ArgumentException("tc::crypto::EccPublicKey()", "curve_type was not supported/valid");

	if (d != nullptr && d_size != 0)
	{
		this->curve_type = curve_type;
		this->d = tc::ByteData(d, d_size);

		tc::crypto::EccKey pub_key;
		GenerateEccPublicKey(pub_key, *this);

		this->Q = pub_key.Q;
	}
}

tc::crypto::EccKey tc::crypto::EccPrivateKey::getPublicKey()
{
	// generate public component if not present
	if (this->Q.data() == nullptr || this->Q.size() == 0)
	{
		tc::crypto::EccKey pub_key;
		GenerateEccPublicKey(pub_key, *this);

		this->Q = pub_key.Q;
	}

	return EccPublicKey(this->curve_type, this->Q.data(), this->Q.size());
}