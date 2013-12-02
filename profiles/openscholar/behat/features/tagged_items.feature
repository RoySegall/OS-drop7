Feature: Testing the tagged items.
  Testing that two nodes tagged to one term and only one node tagged to another
  term.

  @api
  Scenario Outline: verify that the tagged items filter work as expected.
      Given I visit "<first link>"
        And I should see "<first node>"
        And I should see "<second node>"
       When I visit "<second link>"
       Then I should see "<first node>"
        And I should not see "<second node>" under "content"

    Examples:
     | first link         | second link                     | first node                | second node                 |
     | john/blog          | john/blog/science/fire          | First blog                | Second blog                 |
     | john/classes       | john/classes/science/fire       | John F. Kennedy           | Neil Armstrong              |
     | john/documents     | john/documents/science/air      | All about nodes           | All about terms             |
     | john/faq           | john/faq/science/air            | What does JFK stands for? | Where does JFK born?        |
     | john/news          | john/news/science/air           | I opened a new personal   | More tests to the semester  |
     | john/links         | john/links/science/air          | JFK wikipedia page        | Marilyn Monroe              |
     | john/people        | john/people/science/air         | John Fitzgerald Kennedy   | Norma Jeane Mortenson       |
     | john/presentations | john/presentations/science/air  | JFK's biography           | JFK lorem                   |
     | john/publications  | john/publications/science/air   | The Little Prince         | John F. Kennedy: A Biography|
     | john/reader        | john/reader/science/air         | Engadget rss              | Feeds around the world      |
     | john/software      | john/software/science/air       | Mac OSX                   | Windows 7                   |
     #| john/galleries     | john/galleries/air              | Kittens gallery           | JFK                         |
