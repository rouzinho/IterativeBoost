/*======================================================================================================================

    Copyright 2011, 2012, 2013, 2014, 2015 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany

    This file is part of cedar.

    cedar is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    cedar is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with cedar. If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================

    Institute:   Ruhr-Universitaet Bochum
                 Institut fuer Neuroinformatik

    File:        EarSubscriber.h

    Maintainer:  Tutorial Writer Person
    Email:       cedar@ini.rub.de
    Date:        2011 12 09

    Description:

    Credits:

======================================================================================================================*/

// CEDAR INCLUDES
#include "IterativeBoost.h"
#include <cedar/processing/ExternalData.h> // getInputSlot() returns ExternalData
#include <cedar/auxiliaries/MatData.h> // this is the class MatData, used internally in this step
#include "cedar/auxiliaries/math/functions.h"
#include <cmath>



// SYSTEM INCLUDES

//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------
IterativeBoost::IterativeBoost()
:
cedar::proc::Step(true),
mBoostStep(new cedar::aux::DoubleParameter(this,"Boost Step",0.1)),
mBoost(new cedar::aux::MatData(cv::Mat::zeros(1, 1, CV_32F)))
{
this->declareInput("peak detector", true);
this->declareOutput("boost", this->mBoost);
this->connect(this->mBoostStep.get(), SIGNAL(valueChanged()), this, SLOT(reCompute()));

}
//----------------------------------------------------------------------------------------------------------------------
// methods
//----------------------------------------------------------------------------------------------------------------------
void IterativeBoost::compute(const cedar::proc::Arguments&)
{

  //cv::Mat doublepos = op1->getData<cv::Mat>();
  if (auto peak_detector = boost::dynamic_pointer_cast<cedar::aux::ConstMatData>(this->getInput("peak detector")))
  {
    peak = cedar::aux::math::getMatrixEntry<double>(peak_detector->getData(), 0, 0);
  }
  if(peak < 0.5)
  {
     boost_current = boost_current + boost_step;
  }
  /*else
  {
     boost_current = 0;
  }*/
  this->mBoost->getData().at<float>(0, 0) = boost_current;

}

void IterativeBoost::reCompute()
{
   boost_step = this->mBoostStep->getValue();
}



void IterativeBoost::reset()
{

	//ros::shutdown();

}
