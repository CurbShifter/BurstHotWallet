/* 
 * QR Code generator (C++)
 * 
 * Juce convenience class
 * 
 * Copyright (c) Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/qr-code-generator-library
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * - The Software is provided "as is", without warranty of any kind, express or
 *   implied, including but not limited to the warranties of merchantability,
 *   fitness for a particular purpose and noninfringement. In no event shall the
 *   authors or copyright holders be liable for any claim, damages or other
 *   liability, whether in an action of contract, tort or otherwise, arising from,
 *   out of or in connection with the Software or the use or other dealings in the
 *   Software.
 */

#ifndef __JUCE_QR_CODE__
#define __JUCE_QR_CODE__

#include "../JuceLibraryCode/JuceHeader.h"

#include "BitBuffer.hpp"
#include "QrCode.hpp"

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

class JuceQrCodeGenerator
{
public:
	JuceQrCodeGenerator() {};
	~JuceQrCodeGenerator() {};

	Drawable * generateQRpath(const String text, const float dimensionSize)
	{
		const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  // Error correction level
		const QrCode qr = QrCode::encodeText(text.toRawUTF8(), errCorLvl);

		String svgString = qr.toSvgString(0);

		int scale = 100;
		if (dimensionSize > 0)
			scale = jmin<int>(jmax<int>(((float)qr.getSize() / (float)dimensionSize) * 100.f, 0), 100);
		svgString = svgString.replace("100%", String(scale) + "%");

		return juce::Drawable::createFromImageData(svgString.toUTF8(), svgString.getNumBytesAsUTF8());
	}
};

#endif //__JUCE_QR_CODE__
