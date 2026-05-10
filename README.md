# Arknights Endfield Gacha DP Simulator

This project computes the probability distribution for obtaining 6 UP characters in an Arknights Endfield-style gacha system.

The simulator uses dynamic programming instead of Monte Carlo sampling, so the result is deterministic.

## Output

The program writes the result to:

```txt
result.txt
```

Each line contains the pull number and the corresponding probability.

In the code, `_p[i]` is the probability of finishing exactly at pull `i`.

## DP State

We define

$$
dp_s[j][k][b]
$$

as the probability after `s` pulls, where

$$
j = \text{number of pulls since the last 6-star},
$$

$$
k = \text{number of UP characters already obtained},
$$

and

$$
b =
\begin{cases}
1, & \text{the 120-pull guarantee is still active},\\
0, & \text{the 120-pull guarantee is no longer active}.
\end{cases}
$$

The initial state is

$$
dp_0[0][0][1] = 1.
$$

The implementation uses a rolling array:

```cpp
ld dp[2][81][7][2];
```

## 6-star Probability

Let `j` be the pity counter. The 6-star probability is

$$
p(j)=
\begin{cases}
0.008, & j < 65,\\
0.008 + 0.05(j-64), & j \ge 65.
\end{cases}
$$

When `j = 79`, the next pull is treated as hard pity, so a 6-star is guaranteed.

## DP Transition

For a normal pull before hard pity, from state \(dp_s[j][k][b]\), there are three possible transitions.

Getting an UP 6-star:

$$
dp_{s+1}[0][k+1][0]
\mathrel{+}=
dp_s[j][k][b]\cdot p(j)\cdot 0.5.
$$

Getting a non-UP 6-star:

$$
dp_{s+1}[0][k][b]
\mathrel{+}=
dp_s[j][k][b]\cdot p(j)\cdot 0.5.
$$

Not getting a 6-star:

$$
dp_{s+1}[j+1][k][b]
\mathrel{+}=
dp_s[j][k][b]\cdot (1-p(j)).
$$

## 120-pull Guarantee

If no UP character has been obtained before pull 120, then pull 120 gives one UP character directly:

$$
dp_{120}[0][1][0]
\mathrel{+}=
dp_{119}[j][0][1].
$$

This corresponds to the code branch:

```cpp
if(!k && s == 119)
```

## 240-pull Bonus

Every 240 pulls, unfinished states gain one extra UP character:

$$
dp_s[j][k+1][0]
\mathrel{+}=
dp_s[j][k][0].
$$

This is applied at

$$
s \in \{240,480,720,960,1200\}.
$$

## Final Probability

After each pull, we record

Let \(P_{s+1}\) denote the probability of finishing exactly at pull \(s+1\). Then

$$
P_{s+1}
=
\sum_j
\left(
dp_{s+1}[j][6][0]
+
dp_{s+1}[j][6][1]
\right).
$$

In the code, this value is stored as `_p[s + 1]`.

This gives the probability of having obtained all 6 UP characters exactly at pull `s + 1`.

## Build

```bash
g++ -std=c++17 -O2 -o simulator main.cpp
```

## Run

```bash
./simulator
```

The output will be saved in:

```txt
result.txt
```

## Note

The main loop should preferably be written as:

```cpp
for(int s = 0; s < 1200; s++)
```

because the code writes to `_p[s + 1]`, and `_p` has size 1201.
