/*  Copyright 2011 AIT Austrian Institute of Technology
*
*   This file is part of OpenTLD.
*
*   OpenTLD is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   OpenTLD is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with OpenTLD.  If not, see <http://www.gnu.org/licenses/>.
*
*/

/*
 * VarianceFilter.cpp
 *
 *  Created on: Nov 16, 2011
 *      Author: Georg Nebehay
 */

#include "VarianceFilter.h"
#include "DetectorCascade.h"

using namespace cv;

namespace tld
{

VarianceFilter::VarianceFilter()
{
    enabled = true;
    minVar = 0;
}

VarianceFilter::~VarianceFilter()
{
    release();
}

void VarianceFilter::release()
{
  integralImg.release();
  integralImg_squared.release();
}

float VarianceFilter::calcVariance(int *off)
{
    int *ii1 = (int*)integralImg.data;
    double *ii2 = (double*)integralImg_squared.data;

    float mX  = (ii1[off[3]] - ii1[off[2]] - ii1[off[1]] + ii1[off[0]]) / (float) off[5]; //Sum of Area divided by area
    float mX2 = (ii2[off[3]] - ii2[off[2]] - ii2[off[1]] + ii2[off[0]]) / (float) off[5];
    return mX2 - mX * mX;
}

void VarianceFilter::nextIteration(const Mat &img)
{
    if(!enabled) return;

    release();

    cv::integral(img, integralImg, integralImg_squared);
    integralImg = integralImg(cv::Rect(1, 1, img.cols, img.rows));
    integralImg_squared = integralImg_squared(cv::Rect(1, 1, img.cols, img.rows));
    assert(integralImg.type() == CV_32SC1);
    assert(integralImgSquared.type() == CV_64FC1);
}

bool VarianceFilter::filter(int i)
{
    if(!enabled) return true;

    float bboxvar = calcVariance(windowOffsets + TLD_WINDOW_OFFSET_SIZE * i);

    detectionResult->variances[i] = bboxvar;

    if(bboxvar < minVar)
    {
        return false;
    }

    return true;
}

} /* namespace tld */
