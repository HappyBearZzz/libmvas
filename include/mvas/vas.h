#ifndef __VAS_H__
#define __VAS_H__


#include <linux/types.h>
#include <linux/vas.h>

#include <fcntl.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C" {
#endif

#define SYS_vas_create __NR_vas_create
#define SYS_vas_delete __NR_vas_delete
#define SYS_vas_find __NR_vas_find
#define SYS_vas_attach __NR_vas_attach
#define SYS_vas_detach __NR_vas_detach
#define SYS_vas_switch __NR_vas_switch
#define SYS_vas_getattr __NR_vas_getattr
#define SYS_vas_setattr __NR_vas_setattr
#define SYS_active_vas __NR_active_vas
#define SYS_vas_fork __NR_vas_fork
#define SYS_vas_exec __NR_vas_exec

typedef int vasid_t;

/**
 * Create a new VAS.
 *
 * @param[in] name:         The name which the new VAS should have.
 * @param[in] mode:         The access control list for the VAS defining which
 *                          users are allowed to use the VAS in which way. See
 *                          creat(3) for more information about how to specify
 *                          the mode.
 *
 * @returns:                The ID of the VAS on success, -1 on failure (setting
 *                          errno).
 **/
extern vasid_t vas_create(const char * const name, mode_t mode);

/**
 * Delete an existing VAS again.
 *
 * @param[in] vid:          The ID of the VAS which should be deleted.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int vas_delete(vasid_t vid);

/**
 * Find the ID of the VAS with the given name.
 *
 * @param[in] name:         The name of the VAS for which the ID should be found.
 *
 * @returns:                The ID of the VAS on success, -1 on failure (setting
 *                          errno).
 **/
extern vasid_t vas_find(const char * const name);

/**
 * Attach a VAS to a task.
 *
 * @param[in] pid:          The pid of the task to which the VAS should be
 *                          attached, or 0 if the VAS should be attached to
 *                          the current task.
 * @param[in] vid:          The ID of the VAS which should be attached.
 * @param[in] type:         The way in which the VAS should be attached. This
 *                          must be either O_RDONLY, O_RDWR or O_WRONLY. See
 *                          open(3) for more information about the different
 *                          types available.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int vas_attach(pid_t pid, vasid_t vid, int type);

/**
 * Detach a VAS from a task again.
 *
 * @param[in] pid:          The pid of the task from which the VAS should be
 *                          detached, or 0 if the VAS should be detached from
 *                          the current task.
 * @param[in] vid:          The ID of the VAS which should be detached.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int vas_detach(pid_t pid, vasid_t vid);

/**
 * Switch the current address space to the one of the given VAS.
 *
 * @param[in] vid:          The ID of the VAS to whose address space should be
 *                          switched, or 0 if it should be switched back to the
 *                          task's original address space.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int vas_switch(vasid_t vid);

/**
 * Get the ID of the activated VAS for the current task.
 *
 * @returns:                The ID of the active VAS if any, 0 otherwise when the
 *                          task runs in its original AS at the moment.
 **/
extern vasid_t active_vas(void);

/**
 * Get the attributes of a VAS.
 *
 * @param[in] vid:          The ID of the VAS of which the attributes should
 *                          be retrieved.
 * @param[out] attr:        The pointer to the data structure where the
 *                          attributes should be saved in.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int vas_getattr(vasid_t vid, struct vas_attr * const attr);

/**
 * Change the attributes of a VAS.
 *
 * @param[in] vid:          The ID of the VAS of which the attributes should
 *                          be changed.
 * @param[in] attr:         The pointer to the data structure containing the
 *                          new attributes that should be set.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int vas_setattr(vasid_t vid, const struct vas_attr * const attr);

/**
 * Convert the current task's AS into a VAS-CP.
 *
 * @param[in] pid:          The pid of the task for which a checkpoint should
 *                          be taken, or 0 if the checkpoint should be taken of
 *                          the current task.
 *
 * @returns:                The ID of the VAS that contains the CP or -1 on
 *                          failure (setting errno).
 **/
extern vasid_t vas_fork(pid_t pid);

/**
 * Change the current task's AS to a VAS-CP.
 *
 * @param[in] pid:          The pid of the task that should be restored to the
 *                          given checkpoint, or 0 if the current task should be
 *                          restored.
 * @param[in] vid:          The ID of the VAS that contains the checkpoint of
 *                          the application.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int vas_exec(pid_t pid, vasid_t vid);

#ifdef __cplusplus
}
#endif

#endif /* __VAs_H__ */
