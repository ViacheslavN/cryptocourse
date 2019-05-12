#include "pch.h"
#include "SimpleBigNum.h"


CSimpleBigNum::CSimpleBigNum(byte_t *pData , size_t size, bool sign ) :  m_sign(sign)
{
	if (pData && size != 0)
	{
		m_size = size;
		m_pData = (byte_t*)malloc(m_size);

		for (size_t i = 0; i < size; ++i)
		{
			m_pData[size - i - 1] = pData[i];
		}
	}
}

void CSimpleBigNum::Clear()
{
	if (m_pData != nullptr)
	{
		free(m_pData);
		m_pData = nullptr;
	}
}

CSimpleBigNum::~CSimpleBigNum()
{
	Clear();
}

CSimpleBigNum::CSimpleBigNum(const CSimpleBigNum& num) : m_size(num.Size()), m_sign(num.Sign())
{
	if (m_size != 0)
	{
		m_pData = (byte_t*)malloc(m_size);
		memcpy(m_pData, num.m_pData, m_size * sizeof(byte_t));
	}
}

CSimpleBigNum& CSimpleBigNum::operator=(const CSimpleBigNum& num)
{

	Clear();

	m_size = num.Size();
	m_sign = num.Sign();

	if (m_size != 0)
	{
		m_pData = (byte_t*)malloc(num.Size());
		memcpy(m_pData, num.m_pData, num.Size() * sizeof(byte_t));
	}

	return *this;
}

CSimpleBigNum& CSimpleBigNum::operator=(uint32_t num)
{

	Clear();

	uint32_t mask,  shift;
	// Negative number support
	m_sign = 0;  // sign of 0 means positive
	m_size = 4;

	// Figure out the minimum amount of space this "val" will take
	// up in chars (leave at least one byte, though, if “val” is 0).
	for (mask = 0xFF000000; mask > 0x000000FF; mask >>= 8)
	{
		if (num & mask)
		{
			break;
		}
		m_size--;
	}

	if (m_size == 0)
		return *this;

	m_pData = (unsigned char *)malloc(m_size);

	// Now work backwards through the int, masking off each 8-bit
	// byte (up to the first 0 byte) and copy it into the “huge”
	// array in big-endian format.
	mask = 0x000000FF;
	shift = 0;
	for (size_t i = m_size; i; i--)
	{
		m_pData[i - 1] = (num & mask) >> shift;
		mask <<= 8;
		shift += 8;
	}
	
	return *this;
}

void CSimpleBigNum::Init(size_t size, bool sign)
{
	Clear();
	m_size = size;
	m_sign = sign;

	if (m_size != 0)
	{
		m_pData = (byte_t*)malloc(m_size * sizeof(byte_t));
		memset(m_pData, 0, m_size * sizeof(byte_t));
	}
}

size_t CSimpleBigNum::Size() const
{
	return m_size;
}

bool CSimpleBigNum::Sign() const
{
	return m_sign;
}

void CSimpleBigNum::Expand()
{
	unsigned char *pTmp = m_pData;
	m_size += 1;
	m_pData = (byte_t*)malloc(m_size);
	memcpy(m_pData + 1, pTmp, (m_size - 1) * sizeof(byte_t));
	m_pData[0] = 0x01;
	free(pTmp);
}

void CSimpleBigNum::Contract()
{
	int i = 0;

	while (!(m_pData[i]) && (i < m_size))
	{
		i++;
	}

	if (i && i < m_size)
	{
		unsigned char *tmp = &m_pData[i];
		m_pData = (byte_t*)malloc(m_size - i);
		memcpy(m_pData, tmp, m_size - i);
		m_size -= i;
	}
}

void CSimpleBigNum::LeftShift()
{

	int old_carry, carry = 0;

	size_t i = Size();
	do
	{
		i--;
		old_carry = carry;
		carry = (m_pData[i] & 0x80) == 0x80;
		m_pData[i] = (m_pData[i] << 1) | old_carry;
		// Again, if C exposed the overflow bit... 
	} 
	while (i);

	if (carry)
	{
		Expand();
	}
}

void CSimpleBigNum::RightShift()
{
	unsigned int old_carry, carry = 0;

	int i = 0;
	do
	{
		old_carry = carry;
		carry = (m_pData[i] & 0x01) << 7;
		m_pData[i] = (m_pData[i] >> 1) | old_carry;
	}
	while (++i < m_size);

	Contract();
}

int CSimpleBigNum::CompareABS(const CSimpleBigNum& h1, const CSimpleBigNum& h2)
{
	if (h1.Size() > h2.Size())
		return 1;

	if (h1.Size() < h2.Size())
		return -1;

	return 0;
}

int CSimpleBigNum::Compare(const CSimpleBigNum& h1, const CSimpleBigNum& h2)
{
	int comp = CompareABS(h1, h2);

	if (h1.Sign() == h2.Sign())
	{
		if (comp == 0)
			return 0;

		return h1.Sign() ? -comp : comp;
	}
	else
	{
		return h1.Sign() ? -1 : 1;
	}

}

void CSimpleBigNum::Add( CSimpleBigNum& h1, const CSimpleBigNum& h2)
{
	bool resultSign;

	int comp = CompareABS(h1, h2);
	if (comp > 0)
	{
		resultSign = h1.Sign();

		if (h1.Sign() == h2.Sign())
		{
			AddMagnitude(h1, h2);
		}
		else
		{
			SubtractMagnitude(h1, h2);
		}
	}
	else
	{
		CSimpleBigNum tmp;

		// put h1 into tmp and h2 into h1 to swap the operands    
		tmp = h1;
		h1 = h2;
		
		if (h1.Sign() == tmp.Sign())
		{
			resultSign = h1.Sign();
			AddMagnitude(h1, tmp);
		}
		else
		{
			resultSign = h2.Sign();
			SubtractMagnitude(h1, tmp);
		}

	}
	h1.m_sign = resultSign;
}

void CSimpleBigNum::Subtract(CSimpleBigNum& h1, const CSimpleBigNum& h2)
{
	bool resultSign;

	// First compute sign of result, then compute magnitude
	if (CompareABS(h1, h2) > 0)
	{
		resultSign = h1.Sign();

		if (h1.Sign() == h2.Sign())
		{
			SubtractMagnitude(h1, h2);
		}
		else
		{
			AddMagnitude(h1, h2);
		}
	}
	else
	{
		CSimpleBigNum tmp;
		// put h1 into tmp and h2 into h1 to swap the operands
		tmp = h1;
		h1 = h2;

		if (h1.Sign() == tmp.Sign())
		{
			resultSign = !(h1.Sign());
			SubtractMagnitude(h1, tmp);
		}
		else
		{
			resultSign = !(h2.Sign());
			AddMagnitude(h1, tmp);
		}
	}
	// Use the stored sign to set the result
	h1.m_sign = resultSign;
}

void CSimpleBigNum::AddMagnitude( CSimpleBigNum& h1, const CSimpleBigNum& h2)
{
	if (h2.Size() > h1.Size())
	{
		byte_t *pTmp = h1.m_pData;
		h1.m_pData = (byte_t*)malloc(h2.Size());
		memcpy(h1.m_pData + (h2.Size() - h1.Size()), pTmp, h1.Size());
		h1.m_size = h2.m_size;

		free(pTmp);
	}

	uint32_t sum;
	uint32_t carry = 0;

	size_t i = h1.Size();
	size_t j = h2.Size();

	do
	{
		i--;
		if (j)
		{
			j--;
			sum = h1.m_pData[i] + h2.m_pData[j] + carry;
		}
		else
		{
			sum = h1.m_pData[i] + carry;
		}

		carry = sum > 0xFF;
		h1.m_pData[i] = sum;
	} 
	while (i);

	if (carry)
	{
		// Still overflowed; allocate more space 
		h1.Expand();
	}
}

void CSimpleBigNum::SubtractMagnitude(CSimpleBigNum& h1, const CSimpleBigNum& h2)
{
	size_t i = h1.Size();
	size_t j = h2.Size();
	int difference; // signed int - important! 
	unsigned int borrow = 0;

	do
	{
		i--;

		if (j)
		{
			j--;
			difference = h1.m_pData[i] - h2.m_pData[j] - borrow;
		}
		else
		{
			difference = h1.m_pData[i] - borrow;
		}

		borrow = (difference < 0);
		h1.m_pData[i] = difference;
	} 
	while (i);

	if (borrow && i)
	{
		if (h1.m_pData[i - 1]) // Don't borrow i 
		{
			// negative reults are now OK 
			h1.m_pData[i - 1]--;
		}
	}

	h1.Contract();
}

void CSimpleBigNum::Multiply(CSimpleBigNum& h1, const CSimpleBigNum& h2)
{
	bool resultSign;
	CSimpleBigNum temp = h1;

	resultSign = !(h1.Sign() == h2.Sign());

	h1 = 0;
	size_t i = h2.Size();
	do
	{
		i--;
		for (byte_t mask = 0x01; mask; mask <<= 1)
		{
			if (mask & h2.m_pData[i])
			{
				Add(h1, temp);
			}

			temp.LeftShift();
		}
	} 
	while (i);

	h1.m_sign = resultSign;
}

void CSimpleBigNum::Divide(CSimpleBigNum& dividend,  CSimpleBigNum& divisor, CSimpleBigNum* quotient)
{
	int bit_size, bit_position;

	// "bit_position" keeps track of which bit, of the quotient, 
	// is being set or cleared on the current operation.
	bit_size = bit_position = 0;

	// First, left-shift divisor until it's >= than the dividend
	while (CompareABS(divisor, dividend) < 0)
	{
		divisor.LeftShift();
		bit_size++;
	}

	// overestimates a bit in some cases
	if (quotient)
	{
		quotient->Init((bit_size / 8) + 1, !(dividend.Sign() == dividend.Sign()));
	}

	bit_position = 8 - (bit_size % 8) - 1;

	do
	{
		if (CompareABS(divisor, dividend) <= 0)
		{
			SubtractMagnitude(dividend, divisor);  // dividend -= divisor
			if (quotient)
			{
				quotient->m_pData[(int)(bit_position / 8)] |= (0x80 >> (bit_position % 8));
			}
		}

		if (bit_size)
		{
			divisor.RightShift();
		}
		bit_position++;
	} 
	while (bit_size--);
}

void CSimpleBigNum::ModPow(CSimpleBigNum& h1, CSimpleBigNum& exp, CSimpleBigNum& n, CSimpleBigNum& h2)
{
	size_t i = exp.Size();
	byte_t mask;
	CSimpleBigNum tmp1, tmp2;
	
	tmp1 = h1;
	h2 = 1;

	do
	{
		i--;
		for (mask = 0x01; mask; mask <<= 1)
		{
			if (exp.m_pData[i] & mask)
			{
				Multiply(h2, tmp1);
				Divide(h2, n, nullptr);
			}
			// square tmp1
			tmp2 = tmp1;
			Multiply(tmp1, tmp2);
			Divide(tmp1, n, NULL);
		}
	} 
	while (i);
	// Result is now in "h2"
}

void CSimpleBigNum::Inv(CSimpleBigNum&  z, CSimpleBigNum& a)
{
	CSimpleBigNum i, j, y2, y1, y, quotient, remainder, a_temp;

	i = 1;  // initialize for copy
	j = 1;  // initialize for copy
	remainder = 1;  // initialize for copy
	y = 1;
	a_temp = 1;

	y2 = 0;
	y1 = 1;

	i = a;
	j = z;
	if (z.Sign())
	{
		Divide(j, a, NULL);
		// force positive remainder always
		j.m_sign = false;
		Subtract(j, a);
	}

	while (!((j.Size() == 1) && (!j.m_pData[0])))
	{
		remainder = i;
		i = j;
		Divide(remainder, j, &quotient);
		Multiply(quotient, y1); // quotient = y1 * quotient
		y = y2;
		Subtract(y, quotient);  // y = y2 - ( y1 * quotient )

		j = remainder;
		y2 = y1;
		y1 = y;
	}

	z = y2;
	a_temp = a;
	Divide(z, a_temp, nullptr);  // inv_z = y2 % a

	if (z.Sign())
	{
		z.m_sign = false;
		Subtract(z, a_temp);
		if (z.Sign())
		{
			z.m_sign = false;
		}
	}
}