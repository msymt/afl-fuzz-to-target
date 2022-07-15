# AFL: ファズがターゲットに渡るまで

前提：forkserverなし

## ディレクトリ構成

- afl-fuzz.c: 疑似[afl-fuzz.c](https://github.com/google/AFL/blob/master/afl-fuzz.c)
- target.c: ファジング対象

## 動作順序

1. afl-fuzz： `.cur_input`に対してファズを書き込む
2. afl-fuzz： `lseek`により、ファイルの読み書き位置を先頭に戻す
   1. 注：ファズの末尾を指している状態であるため、先頭に戻す必要がある
3. afl-fuzz： 子プロセスのファイルディスクリプタ0(標準入力)を、`.cur_input`のファイルディスクリプタで上書きする(`dup2(out_fd, 0)`)
4. afl-fuzz: 子プロセスは、`exec`によってターゲットを起動する
   1. 注：exec後もファイルディスクリプタは継承される
5. target: 標準入力から文字を取得する
   1. このとき、ファイルディスクリプタ0は`.cur_input`のファイルディスクリプタで上書きされているため、`.cur_input`の中身を読み込む
8. target: 読み込んだ文字列を`out.txt`に書き込む

## Usage

```bash
$ ./make
$ ./afl-fuzz
parent process
child process
Hello,World!
child process exit
$ cat ./out.txt
Hello,World!
```

## ref

- https://www.eidos.ic.i.u-tokyo.ac.jp/~tau/lecture/operating_systems/slides/pdf/07_everything_is_file.pdf
