open Belt;
open Helpers;
module Dict = Js.Dict;
module String = Js.String;

let ids = Fs.readFileLinesSync("./input/day2.txt");

let summarise = line =>
  line
  ->chars_of_string
  ->Array.reduce(
      Dict.empty(),
      (acc, c) => {
        let updated =
          acc->Dict.get(c)->Option.map(v => v + 1)->Option.getWithDefault(1);
        acc->Dict.set(c, updated);
        acc;
      },
    );

let part1 = ids =>
  ids
  ->Array.map(id => {
      let summary = id->summarise->Js.Dict.entries;
      (
        (summary |> Js.Array.find(((_, count)) => count == 2))
        ->Option.mapWithDefault(0, _ => 1),
        (summary |> Js.Array.find(((_, count)) => count == 3))
        ->Option.mapWithDefault(0, _ => 1),
      );
    })
  ->Array.reduce((0, 0), ((a1, a2), (b1, b2)) => (a1 + b1, a2 + b2));

let idsDistance = (a, b) =>
  Array.zip(a->chars_of_string, b->chars_of_string)
  ->Array.reduce((0, ""), ((d, same), (a', b')) =>
      if (a' == b') {
        (d, same ++ a');
      } else {
        (d + 1, same);
      }
    );

let part2 = ids => {
  let rec part2' = (id, rest, top) =>
    switch (rest) {
    | [] => None
    | [next, ...rest'] =>
      let (d, similar) = idsDistance(id, next);
      if (d <= 1) {
        Some(similar);
      } else {
        part2'(id, rest', false)
        ->recoverOption(_ =>
            if (top) {
              part2'(next, rest', true);
            } else {
              None;
            }
          );
      };
    };
  switch (ids) {
  | [] => Some("")
  | [id, ...rest] => part2'(id, rest, true)
  };
};

let () = {
  let p1 = part1(ids);
  Js.log2("Part 1:", p1->fst * p1->snd);
  Js.log2("Part 2:", part2(ids->List.fromArray));
};
