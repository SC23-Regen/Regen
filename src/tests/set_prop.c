/*
 * Copyright Notice for
 * Proactive Data Containers (PDC) Software Library and Utilities
 * -----------------------------------------------------------------------------

 *** Copyright Notice ***

 * Proactive Data Containers (PDC) Copyright (c) 2017, The Regents of the
 * University of California, through Lawrence Berkeley National Laboratory,
 * UChicago Argonne, LLC, operator of Argonne National Laboratory, and The HDF
 * Group (subject to receipt of any required approvals from the U.S. Dept. of
 * Energy).  All rights reserved.

 * If you have questions about your rights to use or distribute this software,
 * please contact Berkeley Lab's Innovation & Partnerships Office at  IPO@lbl.gov.

 * NOTICE.  This Software was developed under funding from the U.S. Department of
 * Energy and the U.S. Government consequently retains certain rights. As such, the
 * U.S. Government has been granted for itself and others acting on its behalf a
 * paid-up, nonexclusive, irrevocable, worldwide license in the Software to
 * reproduce, distribute copies to the public, prepare derivative works, and
 * perform publicly and display publicly, and to permit other to do so.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdc.h"

int
main(int argc, char **argv)
{
    pdcid_t pdc, create_prop1, create_prop2;
    perr_t  ret;
    // pdc_prop_type_t type = PDC_CONT_CREATE;
    int       rank = 0, size = 1;
    PDC_int_t ndim = 3;
    uint64_t  dims[3];
    int       ret_value = 0;

    dims[0] = 64;
    dims[1] = 3;
    dims[2] = 4;
#ifdef ENABLE_MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif

    // create a pdc
    pdc = PDCinit("pdc");

    // create an object property
    create_prop1 = PDCprop_create(PDC_OBJ_CREATE, pdc);
    if (create_prop1 <= 0) {
        printf("Fail to create @ line %d\n", __LINE__);
        ret_value = 1;
    }
    // create another object property
    create_prop2 = PDCprop_create(PDC_OBJ_CREATE, pdc);
    if (create_prop2 <= 0) {
        printf("Fail to create @ line %d\n", __LINE__);
        ret_value = 1;
    }

    ret = PDCprop_set_obj_user_id(create_prop2, 666);
    if (ret != SUCCEED) {
        printf("Fail to set obj user id @ line %d\n", __LINE__);
        ret_value = 1;
    }
    ret = PDCprop_set_obj_data_loc(create_prop2, "somewhere");
    if (ret != SUCCEED) {
        printf("Fail to set obj user id @ line %d\n", __LINE__);
        ret_value = 1;
    }
    ret = PDCprop_set_obj_app_name(create_prop2, "someapp name");
    if (ret != SUCCEED) {
        printf("Fail to set obj user id @ line %d\n", __LINE__);
        ret_value = 1;
    }
    ret = PDCprop_set_obj_time_step(create_prop2, 666);
    if (ret != SUCCEED) {
        printf("Fail to set obj time step @ line %d\n", __LINE__);
        ret_value = 1;
    }
    ret = PDCprop_set_obj_tags(create_prop2, "sometag");
    if (ret != SUCCEED) {
        printf("Fail to set obj time step @ line %d\n", __LINE__);
        ret_value = 1;
    }
    ret = PDCprop_set_obj_dims(create_prop2, ndim, dims);
    if (ret != SUCCEED) {
        printf("Fail to set obj time step @ line %d\n", __LINE__);
        ret_value = 1;
    }
    ret = PDCprop_set_obj_type(create_prop2, PDC_DOUBLE);
    if (ret != SUCCEED) {
        printf("Fail to set obj time step @ line %d\n", __LINE__);
        ret_value = 1;
    }
    ret = PDCprop_set_obj_buf(create_prop2, NULL);
    if (ret != SUCCEED) {
        printf("Fail to set obj time step @ line %d\n", __LINE__);
        ret_value = 1;
    }

    if (PDCprop_close(create_prop1) < 0) {
        printf("Fail to close property @ line %d\n", __LINE__);
        ret_value = 1;
    }
    else {
        printf("successfully close first property\n");
    }
    if (PDCprop_close(create_prop2) < 0) {
        printf("Fail to close property @ line %d\n", __LINE__);
        ret_value = 1;
    }
    else {
        printf("successfully close second property\n");
    }
    // close a pdc
    if (PDCclose(pdc) < 0) {
        printf("fail to close PDC\n");
        ret_value = 1;
    }
#ifdef ENABLE_MPI
    MPI_Finalize();
#endif
    return ret_value;
}
