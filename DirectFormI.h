/*******************************************************************************

This header file has been taken from:
"A Collection of Useful C++ Classes for Digital Signal Processing"
By Vinnie Falco 

Bernd Porr adapted it for Linux and turned it into a filter using
fixed point arithmetic.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vinnie Falco
Copyright (C) 2013, Bernd Porr, mail@berndporr.me.uk

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/



#ifndef DIRECT_FORM_I_H
#define DIRECT_FORM_I_H

class DirectFormI
{
public:
	// constructor with the coefficients b0,b1,b2 for the FIR part
        // and a1,a2 for the IIR part. a0 is always one.
	// the coefficients have been scaled up by the factor
	// 2^q which need to scaled down by this factor after every
	// time step which is taken care of.
	DirectFormI(const short int b0, const short int b1, const short int b2, 
		    const short int a1, const short int a2, 
		    const short int q = 15)
	{
		// coefficients are scaled by factor 2^q
		q_scaling = q;
		// FIR coefficients
		c_b0 = b0;
		c_b1 = b1;
		c_b2 = b2;
		// IIR coefficients
		c_a1 = a1;
		c_a2 = a2;
		reset();
	}
	
	void reset ()
	{
		m_x1 = 0;
		m_x2 = 0;
		m_y1 = 0;
		m_y2 = 0;
	}

	// filtering operation: one sample in and one out
	short int filter(const short int in)
	{
		// calculate the output
		int out_upscaled = (int)c_b0*(int)in
			+ (int)c_b1*(int)m_x1 
			+ (int)c_b2*(int)m_x2
			- (int)c_a1*(int)m_y1 
			- (int)c_a2*(int)m_y2;

		// scale it back from int to short int
		short int out = out_upscaled >> q_scaling;

		// update the delay lines
		m_x2 = m_x1;
		m_y2 = m_y1;
		m_x1 = in;
		m_y1 = out;

		return out;
	}
	
private:
	// delay line
  	short int m_x2; // x[n-2]
  	short int m_y2; // y[n-2]
  	short int m_x1; // x[n-1]
  	short int m_y1; // y[n-1]

	// coefficients
  	short int c_b0,c_b1,c_b2; // FIR
  	short int c_a1,c_a2; // IIR

	// scaling factor
	short int q_scaling; // 2^q_scaling
};

#endif
