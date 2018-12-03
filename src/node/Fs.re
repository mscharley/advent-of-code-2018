[@bs.module "fs"] external readFileSync: string => Buffer.t = "";

let readFileLinesSync: string => array(string) =
  file =>
    readFileSync(file)->Buffer.toString
    |> Js.String.split("\n")
    |> Js.Array.filter(n => n != "");
