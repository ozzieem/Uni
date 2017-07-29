if (! this.sh_languages) {
  this.sh_languages = {};
}
sh_languages['bibtex'] = [
  [
    [
      /\b(?:article|incollection|inbook|inproceedings|techreport)\b/g,
      'sh_keyword',
      -1
    ],
    [
      /\b(?:author|title|journal|volume|number|year|pages|booktitle|publisher|editor|chapter|institution)\b/g,
      'sh_type',
      -1
    ]
  ]
];
