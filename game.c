#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PLAYER_CARDS 5
#define CPU_CARDS 6
#define JOKER 99 // ジョーカーの値を99とする

// プレイヤーの手札を表示
void displayPlayerHand(int hand[], int size) {
    printf("あなたの手札: ");
    for (int i = 0; i < size; i++) {
        printf("[%d] ", hand[i]);
    }
    printf("\n");
}

// CPUの手札をシャッフル
void shuffleCPUHand(int hand[], int size) {
    for (int i = 0; i < size; i++) {
        int j = rand() % size;
        int temp = hand[i];
        hand[i] = hand[j];
        hand[j] = temp;
    }
}

// ペアを削除する
int removePairs(int hand[], int size) {
    int newSize = size;
    for (int i = 0; i < newSize - 1; i++) {
        for (int j = i + 1; j < newSize; j++) {
            if (hand[i] == hand[j]) {
                printf("ペアが見つかりました: %d と %d を捨てます。\n", hand[i], hand[j]);
                // ペアを削除
                for (int k = j; k < newSize - 1; k++) {
                    hand[k] = hand[k + 1];
                }
                for (int k = i; k < newSize - 2; k++) {
                    hand[k] = hand[k + 1];
                }
                newSize -= 2; // 手札サイズを2減らす
                i = -1; // ループを再スタート
                break;
            }
        }
    }
    return newSize;
}

// カードを引く処理
int drawCard(int playerHand[], int playerSize, int cpuHand[], int *cpuSize) {
    int cardIndex;

    // CPUの手札を表示せず、カードを引かせる
    printf("CPUの手札は %d 枚あります。\n", *cpuSize);
    printf("どのカードを引きますか？ (1～%d): ", *cpuSize);
    scanf("%d", &cardIndex);
    cardIndex--; // インデックスを0始まりに調整

    // 引いたカードを確認
    int drawnCard = cpuHand[cardIndex];
    printf("カード [%d] を引きました！\n", drawnCard);

    // ジョーカーを引いたらゲーム終了
    if (drawnCard == JOKER) {
        printf("ジョーカーを引きました！ゲーム失敗です。\n");
        exit(0);
    }

    // 引いたカードをプレイヤーの手札に追加
    playerHand[playerSize] = drawnCard;

    // CPUの手札から引いたカードを削除
    for (int i = cardIndex; i < *cpuSize - 1; i++) {
        cpuHand[i] = cpuHand[i + 1];
    }
    (*cpuSize)--;

    return playerSize + 1;
}

int main() {
    int playerHand[PLAYER_CARDS + CPU_CARDS]; // プレイヤーが最大CPUの手札をすべて持てるようにする
    int cpuHand[CPU_CARDS] = {1, 2, 3, 4, 5, JOKER}; // 99はジョーカーを表現
    int playerSize = PLAYER_CARDS, cpuSize = CPU_CARDS;

    // プレイヤーの手札を初期化
    for (int i = 0; i < PLAYER_CARDS; i++) {
        playerHand[i] = i + 1;
    }

    srand(time(NULL));

    // CPUの手札をシャッフル
    shuffleCPUHand(cpuHand, CPU_CARDS);

    // プレイヤーの手札からペアを削除
    printf("ゲーム開始！\n");
    playerSize = removePairs(playerHand, playerSize);

    // ゲームループ
    while (playerSize > 0 && cpuSize > 0) {
        printf("\nあなたのターンです。\n");
        displayPlayerHand(playerHand, playerSize);

        // CPUのカードを引く
        playerSize = drawCard(playerHand, playerSize, cpuHand, &cpuSize);

        // プレイヤーの手札からペアを削除
        playerSize = removePairs(playerHand, playerSize);
    }

    // 勝敗判定
    printf("\nおめでとうございます！ババ（ジョーカー）を引かずに勝ちました！\n");

    return 0;
}
