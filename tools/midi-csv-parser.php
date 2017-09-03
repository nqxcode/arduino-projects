#!/usr/bin/env php
<?php

if (!isset($argv[1])) {
    echo 'Please, specify path to midi in csv...' . PHP_EOL;
    return;
}

$maxNotesCount = 496;
if (isset($argv[2])) {
    $maxNotesCount = (float)$argv[2];
}

$notes = [];

$midi = [];
$a = 440; // a is 440 hz...
for ($x = 0; $x < 127; ++$x) {
    $midi[$x] = round(pow(2, ($x - 69) / 12) * $a);
}

if (($handle = @fopen($argv[1], 'r')) !== false) {
    while (($data = fgetcsv($handle, 1000, ',')) !== false) {
        $data = array_map(function ($v) {
            return trim($v);
        }, $data);

        $type = $data[2];
        if ($type === 'Note_on_c') {
            $note = $data[4];
            $absoluteTime = $data[1];

            $notes[$absoluteTime] = $midi[$note];
        }
    }
    fclose($handle);
}


if (count($notes) > 0) {
    echo 'Notes (Hz):' . PHP_EOL;
    echo implode(', ', array_slice($notes, 0, $maxNotesCount));

    $keys = array_slice(array_keys($notes), 0, $maxNotesCount);

    $durations = [];
    for ($i = 1; $i < count($keys); $i++) {
        $durations[] = $keys[$i] - $keys[$i - 1];
    }

    $durations[] = ($keys[$i - 1] - $keys[$i - 2]) * 2; // duration for last note

    echo PHP_EOL . 'Note durations (ms): ' . PHP_EOL;
    echo implode(', ', $durations) . PHP_EOL;

}
