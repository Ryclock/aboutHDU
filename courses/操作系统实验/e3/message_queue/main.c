#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <errno.h>

#define MSG_SIZE 256
#define END_MSG "endl"
#define END_ASK_MSG1 "over1"
#define END_ASK_MSG2 "over2"

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

struct sender_info {
    long msg_type;
    sem_t *sem_close_p;
};

const long sender1_msg_type = 1, sender2_msg_type = 2, ask_delta = 3;

int msg_queue_id;
sem_t sem_close_sender1, sem_close_sender2, sem_not_used, sem_not_empty, sem_screen;

void create_msg_queue() {
    key_t key = ftok("/tmp/my_msg_que", getpid());
    msg_queue_id = msgget(key, IPC_CREAT | 0666);

    if (msg_queue_id == -1) {
        perror("Error creating msg queue");
        exit(EXIT_FAILURE);
    }
}

void delete_msg_queue() {
    struct msqid_ds buf;
    while (1){
        sem_wait(&sem_not_used);
        msgctl(msg_queue_id, IPC_STAT, &buf);
        if(buf.msg_qnum==0){
            break;
        }
        sem_post(&sem_not_used);
        sleep(0.1);
    }
    if (msgctl(msg_queue_id, IPC_RMID, NULL) == -1) {
        perror("msgctl");
    }
    sem_post(&sem_not_used);
}

void send_msg(const char *msg_text, int sender_id) {
    struct msg_buffer msg;
    msg.msg_type = sender_id;
    strcpy(msg.msg_text, msg_text);

    sem_wait(&sem_not_used);
    if (msgsnd(msg_queue_id, &msg, sizeof(msg), IPC_NOWAIT) == -1) {
        if (errno != EAGAIN) {
            perror("msgsnd");
        }
    }else{
        sem_post(&sem_not_empty);
    }
    sem_post(&sem_not_used);
}

void receive_msg(struct msg_buffer *msg_p, int msg_len, int msg_type){
    sem_wait(&sem_not_used);
    if (msgrcv(msg_queue_id, msg_p, msg_len, msg_type, IPC_NOWAIT) == -1) {
        if (errno != ENOMSG) {
            perror("msgrcv");
        }
    }
    sem_post(&sem_not_used);
}

void *receiver(void *arg) {
    struct msg_buffer msg;
    int over_cnt = 0;

    while (1) {
		memset(&msg, 0, sizeof(msg));
        sem_wait(&sem_not_empty);
        receive_msg(&msg, sizeof(msg), -ask_delta);
        if(msg.msg_type==0){
            sem_post(&sem_not_empty);
            continue;
        }

        sem_wait(&sem_screen);
        printf("Receiver: Received msg from sender%ld: %s\n", msg.msg_type, msg.msg_text);
        sem_post(&sem_screen);

        if (strcmp(msg.msg_text, END_MSG) != 0) {
            continue;
        }

        if (msg.msg_type == sender1_msg_type) {
            send_msg(END_ASK_MSG1, msg.msg_type+ask_delta);
            sem_post(&sem_close_sender1);
            over_cnt++;
        } else if (msg.msg_type == sender2_msg_type) {
            send_msg(END_ASK_MSG2, msg.msg_type+ask_delta);
            sem_post(&sem_close_sender2);
            over_cnt++;
        } else {
            perror("receiver");
        }

        if (over_cnt==2) {
            break;
        }
    }

    delete_msg_queue();

    pthread_exit(NULL);
}

void *sender(void *arg) {
    struct sender_info *info=(struct sender_info *)arg;
    if(info->msg_type == sender1_msg_type){
        create_msg_queue();
    }

    char input_msg[MSG_SIZE];
    while (1) {
        sem_wait(&sem_screen);
        printf("Sender%ld: Enter a message (type 'exit' to quit): ", info->msg_type);
        fgets(input_msg, sizeof(input_msg), stdin);
        sem_post(&sem_screen);
        input_msg[strcspn(input_msg, "\n")] = '\0';
        if (strcmp(input_msg, "exit") == 0) {
            send_msg(END_MSG, info->msg_type);
            break;
        }
        send_msg(input_msg, info->msg_type);
    }

    struct msg_buffer msg;
    memset(&msg, 0, sizeof(msg));
    sem_wait(info->sem_close_p);
    sem_wait(&sem_not_empty);
    receive_msg(&msg, sizeof(msg), info->msg_type+ask_delta);

    sem_wait(&sem_screen);
    printf("Sender%ld: Received msg from receiver: %s\n", info->msg_type, msg.msg_text);
    sem_post(&sem_screen);

    pthread_exit(NULL);
}

int main() {
    sem_init(&sem_close_sender1, 0, 0);
    sem_init(&sem_close_sender2, 0, 0);
    sem_init(&sem_not_used, 0, 1);
    sem_init(&sem_not_empty, 0, 0);
    sem_init(&sem_screen, 0, 1);

    struct sender_info info1, info2;
    info1.msg_type = sender1_msg_type;
    info1.sem_close_p = &sem_close_sender1;
    info2.msg_type = sender2_msg_type;
    info2.sem_close_p = &sem_close_sender2;

    pthread_t sender1_thread, sender2_thread, receiver_thread;

	pthread_create(&sender1_thread, NULL, sender, &info1);
	pthread_create(&sender2_thread, NULL, sender, &info2);
	pthread_create(&receiver_thread, NULL, receiver, NULL);

    pthread_join(sender1_thread, NULL);
    pthread_join(sender2_thread, NULL);
    pthread_join(receiver_thread, NULL);

    sem_destroy(&sem_close_sender1);
    sem_destroy(&sem_close_sender2);
    sem_destroy(&sem_not_used);
    sem_destroy(&sem_not_empty);
    sem_destroy(&sem_screen);

    return 0;
}
