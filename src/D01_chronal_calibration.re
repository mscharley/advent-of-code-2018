let lines = Fs.readFileLinesSync("./input/day1.txt");
let inputs =
  lines->Belt.Array.map(n =>
    (
      n->String.sub(0, 1),
      int_of_string(n->String.sub(1, n->String.length - 1)),
    )
  );

let part2Cache = Js.Dict.empty();
part2Cache->Js.Dict.set("0", true);
let result =
  inputs->Belt.Array.reduce(
    0,
    (acc, (op, v)) => {
      let res =
        switch (op) {
        | "+" => acc + v
        | "-" => acc - v
        | _ => raise(Not_found)
        };

      /* Verified via trial and error, we won't see the same frequency in the first pass */
      part2Cache->Js.Dict.set(res->string_of_int, true);
      res;
    },
  );

Js.log2("Part 1:", result);

let found = ref(false);
let index = ref(0);
let loop = Js.Array.length(inputs);
let acc = ref(result);
while (! found^) {
  let (op, v) = inputs->Array.get(index^ mod loop);
  acc :=
    (
      switch (op) {
      | "+" => acc^ + v
      | "-" => acc^ - v
      | _ => raise(Not_found)
      }
    );
  if (part2Cache
      ->Js.Dict.get((acc^)->string_of_int)
      ->Belt.Option.getWithDefault(false)) {
    Js.log2("Part 2:", acc^);
    found := true;
  };
  part2Cache->Js.Dict.set((acc^)->string_of_int, true);
  index := index^ + 1;
};
