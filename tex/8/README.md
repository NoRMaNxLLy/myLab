# testing how section numbers would look like with arabic text

By default section numbers will be displayed in reverse. this can be
fixed with this set of renew commands:

```
% \arabic is internally defined by LaTeX
\renewcommand{\thesection} {\arabic{section}}
\renewcommand{\thesubsection} {\arabic{subsection}.\arabic{section}}
\renewcommand{\thesubsubsection} {\arabic{subsubsection}.\arabic{subsection}.\arabic{section}}
```

the `\arabic` commands displays counters with arabic digits (1 2 3..).

## Reference

* an arabic template for summarizing teaching and research activities.
  <https://www.overleaf.com/latex/templates/med-report-arabic/mvfzkjnrcznz>
