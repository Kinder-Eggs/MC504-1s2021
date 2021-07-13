#include <linux/syscalls.h>
#include <linux/user_namespace.h>

int weights[65536] = {[0 ... 65535] = 10};  // Initializes all weights as 10

SYSCALL_DEFINE1(getuserweight, int, uid) {
	if(uid < -1 || uid > 65535)  // Invalid uid
		return  -EINVAL;
	if(uid == -1)  // uid = -1  ->  Current user
		uid = from_kuid_munged(current_user_ns(), current_uid());  // Takes current user uid as shown on syscall 102
	return weights[uid];
}

SYSCALL_DEFINE2(setuserweight, int, uid, int, weight) {
	if(from_kuid_munged(current_user_ns(), current_uid()) != 0) {  // Makes sure its called by sudo user
		return -EACCES;
	}
	if(uid < -1 || uid > 65535 || weight <= 0) {  // Invalid uid or weight
		return -EINVAL;
	}
	if(uid == -1)
		uid = from_kuid_munged(current_user_ns(), current_uid());
	weights[uid] = weight;
	return 0;
}
