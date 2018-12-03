open Belt;
open Helpers;
module Regex = Js.Re;

type rectangle = {
  x: int,
  y: int,
  width: int,
  height: int,
};

type claim = {
  id: int,
  position: rectangle,
};

let claims = Fs.readFileLinesSync("./input/day3.txt");

let safeCapture: (Regex.result, int) => option(string) =
  (result, index) =>
    result
    ->Regex.captures
    ->Array.get(index)
    ->Option.flatMap(v => v->Js.Nullable.toOption);

let claimRe =
  Regex.fromStringWithFlags(
    "^#(\\d+) @ (\\d+),(\\d+): (\\d+)x(\\d+)$",
    ~flags="m",
  );
let parseClaim = line =>
  claimRe
  |> Regex.exec(line)
  |> (
    fun
    | Some(result) =>
      Some({
        id: result->safeCapture(1)->Option.getExn->int_of_string,
        position: {
          x: result->safeCapture(2)->Option.getExn->int_of_string,
          y: result->safeCapture(3)->Option.getExn->int_of_string,
          width: result->safeCapture(4)->Option.getExn->int_of_string,
          height: result->safeCapture(5)->Option.getExn->int_of_string,
        },
      })
    | None => None
  );

let mapClaims = (claims, size) =>
  claims->Array.reduce(
    (Array.make(size * size, 0), size),
    ((sheet, size), claim) => {
      let position = claim.position;
      for (x in position.x to position.x + position.width - 1) {
        for (y in position.y to position.y + position.height - 1) {
          let index = y * size + x;
          Array.getExn(sheet, index) + 1 |> Array.setExn(sheet, index);
        };
      };

      (sheet, size);
    },
  );

let part1 = sheet => sheet->countElements(n => n >= 2);

let part2 = ((sheet, size), claims) =>
  claims
  |> Js.Array.find(c => {
       let success = ref(true);
       let position = c.position;
       for (x in position.x to position.x + position.width - 1) {
         for (y in position.y to position.y + position.height - 1) {
           let index = y * size + x;
           success := success^ && Array.getExn(sheet, index) <= 1;
         };
       };

       success^;
     });

let () = {
  let size = 1000;
  let claims' = claims->Array.map(c => parseClaim(c)->Option.getExn);
  let overlaps = claims'->mapClaims(size);
  Js.log2("Part 1:", overlaps->fst->part1);
  Js.log2("Part 2:", overlaps->part2(claims')->Option.getExn.id);
};
