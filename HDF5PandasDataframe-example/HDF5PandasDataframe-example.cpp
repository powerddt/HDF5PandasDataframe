/****************************************************************************

Copyright (c) 2018, Xi Wang & Jinan Bayes Information Technology Co., Ltd.
All rights reserved.

License: BSD 3-Clause
Created: June 15, 2018
Author:  Xi Wang - powerddt@163.com

****************************************************************************/

#pragma once

#include <hdf5.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stdafx.h"
#include "H5ATTR.h"
#include "HDF5PandasDataframe.h"

#define FILE            "dataframe.h5"
#define NCOL			62	
#define NROW			100
#define COL_STR_LEN_MAX 5

#ifdef __cplusplus
extern "C" {
#endif

int main()
{
	// create test data
	char test_cols[NCOL][COL_STR_LEN_MAX] = { 0 };
	strcpy(test_cols[0], "open");
	strcpy(test_cols[1], "high");
	strcpy(test_cols[2], "low");
	strcpy(test_cols[3], "close");

	for (int i = 4; i < NCOL; i++)
	{
		sprintf(test_cols[i], "ma%d", i - 2);
	}

	double test_data[NROW][NCOL];
	unsigned long long test_tick[NROW];

	for (int i = 0; i < NCOL; i++)
	{
		for (int j = 0; j < NROW; j++)
		{
			test_data[j][i] = 25530.00+i+j;
		}
	}

	test_tick[0] = 1503671401000000000;
	for (int i = 1; i < NROW; i++)
	{
		test_tick[i] = test_tick[i - 1]+ 1000000000;
		fprintf(stderr, "%lld\n", test_tick[i]);
	}


	// hdf5 file
	hid_t file = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

	// group: /data
	hid_t group_id = H5Gcreate(file, "/data", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	herr_t status = Bayes_H5Aset_group_global_attributes(group_id);

	// dataframe group: /data/sec1
	DATAFRAME df;
	df.column = test_cols;
	df.index = test_tick;
	df.data = test_data;
	Bayes_H5Gset_create_dataframe_group2(group_id, "/data/sec1", NCOL, NROW, COL_STR_LEN_MAX, df);

	status = H5Gclose(group_id);
	status = H5Fclose(file);

	//getchar();

	return 0;
}

#ifdef __cplusplus
}
#endif