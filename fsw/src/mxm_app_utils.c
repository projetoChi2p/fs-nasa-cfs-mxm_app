/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * \file
 *   This file contains the source code for the Sample App utility functions
 */

/*
** Include Files:
*/
#include "mxm_app.h"
#include "mxm_app_eventids.h"
#include "mxm_app_tbl.h"
#include "mxm_app_utils.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify contents of First Example Table buffer contents          */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MXM_APP_TblValidationFunc(void *TblData)
{
    int32                      ReturnCode = CFE_SUCCESS;
    MXM_APP_ExampleTable_t *TblDataPtr = (MXM_APP_ExampleTable_t *)TblData;

    /*
    ** Sample Example Table Validation
    */
    if (TblDataPtr->Int1 > MXM_APP_TBL_ELEMENT_1_MAX)
    {
        /* First element is out of range, return an appropriate error code */
        ReturnCode = MXM_APP_TABLE_OUT_OF_RANGE_ERR_CODE;
    }

    return ReturnCode;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Output CRC                                                      */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MXM_APP_GetCrc(const char *TableName)
{
    int32          status;
    uint32         Crc;
    CFE_TBL_Info_t TblInfoPtr;

    status = CFE_TBL_GetInfo(&TblInfoPtr, TableName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Sample App: Error Getting Example Table Info");
    }
    else
    {
        Crc = TblInfoPtr.Crc;
        CFE_ES_WriteToSysLog("Sample App: CRC: 0x%08lX\n\n", (unsigned long)Crc);
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/*                                                                            */
/* Restore application context from Critical Data Storage (CDS)               */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
int32 MXM_APP_RestoreContextCDS(void) {
    int32  status;
    int32   buff [3];

    status = CFE_ES_RestoreFromCDS((uint8*)buff, MXM_APP_Data.CDSHandle);

    if (status == CFE_SUCCESS)
    {
        MXM_APP_Data.RandomizingSeed_1 = buff[0];
        MXM_APP_Data.RandomizingSeed_2 = buff[1];
        MXM_APP_Data.RandomizingSeed_3 = buff[2];
    }
    else
    {
        status = CFE_ES_CDS_ACCESS_ERROR;
    }

    return status;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/*                                                                            */
/* Save application context at the Critical Data Storage (CDS)                */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
int32 MXM_APP_SaveContextCDS(void)
{
    int32 status;
    int32 buff [3];

    buff[0] = MXM_APP_Data.RandomizingSeed_1;
    buff[1] = MXM_APP_Data.RandomizingSeed_2;
    buff[2] = MXM_APP_Data.RandomizingSeed_3;

    status = CFE_ES_CopyToCDS(MXM_APP_Data.CDSHandle, buff);

    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Erro saving at CDS.\n");
        status = CFE_ES_CDS_ACCESS_ERROR;
    }

    return status;
}
