#ifndef __RIMRAF_H__
#define __RIMRAF_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Remove directory recursively.
 * Returns zero on success, otherwise returns non zero.
 */
extern int rmrf(const char* directory);


#ifdef __cplusplus
}
#endif

#endif
