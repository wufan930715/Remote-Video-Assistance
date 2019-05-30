/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_oits_ndk_JNI */

#ifndef _Included_com_oitp_msg_MsgJNI
#define _Included_com_oitp_msg_MsgJNI
#ifdef __cplusplus
extern "C" {
#endif

//ɾ���¼����
JNIEXPORT void JNICALL Java_com_oitp_msg_MsgJNI_detachEventHandler(JNIEnv *env, jobject thiz);
//�����¼����
JNIEXPORT void JNICALL Java_com_oitp_msg_MsgJNI_setEventHandler(JNIEnv *env, jobject thiz, jobject eventHandler);

/*
 * Class:     com_oits_ndk_JNI
 * Method:    initJNI
 * Signature: (Ljava/lang/String;IZ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_oitp_msg_MsgJNI_initJNI
  (JNIEnv *env, jobject thiz, jstring addr, jint port,jboolean bOpenGlEs20);

/*
 * Class:     com_oits_ndk_JNI
 * Method:    releaseJNI
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_oitp_msg_MsgJNI_releaseJNI
  (JNIEnv * env, jobject thiz);

/*
 * Class:     com_oits_ndk_JNI
 * Method:    login
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_oitp_msg_MsgJNI_login
  (JNIEnv *env, jclass clz,jint uid,jint utype,jstring usrName,jstring realName,jstring code,jint timestmap);

/*
 * Class:     com_oits_ndk_JNI
 * Method:    sendTextMessage
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_oitp_msg_MsgJNI_sendTextMessage
  (JNIEnv *env, jclass clz, jint dstId,jint dstType,jint relationType,jint msgType, jstring message, jint fileSize, jint timeLen, jint sequence);

/*
*	����Ŀ�����ID
*/
JNIEXPORT void JNICALL Java_com_oitp_msg_MsgJNI_setDstRoom(JNIEnv *env, jclass clz, jint dstRoomID,jint nTeacherID);
/*
*	����ڰ����
*/
JNIEXPORT jstring JNICALL Java_com_oitp_msg_MsgJNI_computeBoardScale(JNIEnv *env, jclass clz, jint scx,jint scy,jint dcx,jint dcy);
/*
* ��ʼ¼��
*/
JNIEXPORT void JNICALL Java_com_oitp_msg_MsgJNI_startRecord(JNIEnv *env, jclass clz);
/*
* ֹͣ¼��
*/
JNIEXPORT void JNICALL Java_com_oitp_msg_MsgJNI_stopRecord(JNIEnv *env, jclass clz);
/*
* ���ñ����С
*/
JNIEXPORT jboolean JNICALL Java_com_oitp_msg_MsgJNI_setEncodeSize(JNIEnv *env, jclass clz,jint w,jint h,jint nType);
/*
* ��ʼ��Ƶ����
*/
JNIEXPORT jboolean JNICALL Java_com_oitp_msg_MsgJNI_startVideoEncode(JNIEnv *env, jclass clz);
/*
* ֹͣ��Ƶ����
*/
JNIEXPORT jboolean JNICALL Java_com_oitp_msg_MsgJNI_stopVideoEncode(JNIEnv *env, jclass clz);

/*
* //������Ƶ����
*/
JNIEXPORT jint JNICALL Java_com_oitp_msg_MsgJNI_encodeVideoData(JNIEnv *env, jclass clz,jintArray imgBuf1,jint w,jint h);

/*
* ���;���Э��
*/
JNIEXPORT jboolean JNICALL Java_com_oitp_msg_MsgJNI_myUpHand(JNIEnv *env, jclass clz);
/*
* ��ʼ���ſμ�
*/
JNIEXPORT jboolean JNICALL Java_com_oitp_msg_MsgJNI_startPlayCwd(JNIEnv *env, jclass clz,jstring cwdFile);
/*
* ��ͣ���ſμ�
*/
JNIEXPORT jboolean JNICALL Java_com_oitp_msg_MsgJNI_pausePlayCwd(JNIEnv *env, jclass clz,jboolean bPause);
/*
* ֹͣ���ſμ�
*/
JNIEXPORT jboolean JNICALL Java_com_oitp_msg_MsgJNI_stopPlayCwd(JNIEnv *env, jclass clz);
/*
* �����������
*/
JNIEXPORT void JNICALL Java_com_oitp_msg_MsgJNI_checkNetConnect(JNIEnv *env, jclass clz);
/*
* �˳���¼
*/
JNIEXPORT void JNICALL Java_com_oitp_msg_MsgJNI_loginOut(JNIEnv *env, jclass clz);

#ifdef __cplusplus
}
#endif
#endif
