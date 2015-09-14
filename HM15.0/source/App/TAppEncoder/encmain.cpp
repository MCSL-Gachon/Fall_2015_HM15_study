/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.  
 *
 * Copyright (c) 2010-2014, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     encmain.cpp
    \brief    Encoder application main
*/

#include <time.h>
#include <iostream>
#include "TAppEncTop.h"
#include "TAppCommon/program_options_lite.h"

using namespace std;
namespace po = df::program_options_lite;

//! \ingroup TAppEncoder
//! \{

// ====================================================================================================================
// Main function
// ====================================================================================================================

int main(int argc, char* argv[])
{
  TAppEncTop  cTAppEncTop;	//TAppEncTop(인코더 최상위 클래스) 객체 생성, TAppEncTop는 TAppEncCfg(인코딩 옵션을 처리하기 위한 클래스)를 상속받음

  // print information
  //인코더 정보 출력
  fprintf( stdout, "\n" );
  fprintf( stdout, "HM software: Encoder Version [%s]", NV_VERSION );
  fprintf( stdout, NVM_ONOS );
  fprintf( stdout, NVM_COMPILEDBY );
  fprintf( stdout, NVM_BITS );
  fprintf( stdout, "\n" );

  // create application encoder class
  cTAppEncTop.create(); //TAppEncCfg 클래스에서 상속 받은 메서드지만 아무 것도 수행하지 않음

  // parse configuration
  try
  {
	  //TAppEncCfg 클래스에서 상속 받은 메서드로 사용자가 입력한 매개변수를 파싱하여 인코딩 옵션 설정
	  /*
	  TAppEncTop.parseCfg()의 실행 흐름
	  1. 인코더에서 사용하는 옵션들을 po::Options 구조체 내부에 존재하는 리스트에 추가한다.
	  2. 리스트의 추가된 옵션들을 디폴트 값으로 세팅
	  3. 사용자가 입력한 매개변수 및 입력된 옵션 값들이 정상적인 값인지 체크
	  4. 전역 변수들의 값을 설정하고, 설정된 주요 옵션 값을 화면에 출력한다.
	  */
    if(!cTAppEncTop.parseCfg( argc, argv )) 
    {
		//설정 값들이 제대로 파싱되지 않은 경우 프로그램을 종료시키는 루틴이지만  TAppEncTop.destroy()는 아무 것도 수행하지 않음
      cTAppEncTop.destroy();
      return 1;
    }
  }
  catch (po::ParseFailure& e) // 정상적으로 파싱되지 않은 옵션들을 출력
  {
    cerr << "Error parsing option \""<< e.arg <<"\" with argument \""<< e.val <<"\"." << endl;
    return 1;
  }

  // starting time
  
  double dResult;
  long lBefore = clock();

  // call encoding function
  // 실제로 인코딩이 시작되는 지점
  cTAppEncTop.encode();

  // ending time
  dResult = (double)(clock()-lBefore) / CLOCKS_PER_SEC;
  printf("\n Total Time: %12.3f sec.\n", dResult);

  // destroy application encoder class
  cTAppEncTop.destroy();

  return 0;
}

//! \}
