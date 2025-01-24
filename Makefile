# コンパイラとフラグの設定
CC = gcc
CFLAGS = -Wall -g

# ソースファイルがあるディレクトリ
SRCDIR = src

# ソースファイルのリスト
SRCS = $(wildcard $(SRCDIR)/*.c)

# オブジェクトファイルのリスト
OBJS = $(SRCS:$(SRCDIR)/%.c=%.o)

# 出力実行ファイル
EXEC = wordle

# デフォルトターゲット（make実行時に呼ばれる）
all: $(EXEC)

# 実行ファイルの作成
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) -lncurses

# オブジェクトファイルの作成
%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンターゲット（ビルドファイルを削除）
clean:
	rm -f $(OBJS) $(EXEC)

# インストールターゲット（任意で作成）
install:
	@echo "Installing $(EXEC)..."
	@# 実行ファイルを適切な場所にコピーする処理を記述することができます。

# テストターゲット（任意で作成）
test:
	@echo "Running tests..."
	@# 必要に応じてテストスクリプトを呼び出すことができます。

