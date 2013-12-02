Feature:
  Testing ability to add links to the primary menu.

  @api
  Scenario Outline: Test adding a link.
    Given I am logging in as "john"
     When I visit "john/cp/menu/nojs/new/primary-menu"
      And I select "url" from "type"
      And I press "Continue"
      And I fill in "title" with <title>
      And I populate in "url" with <url>
      And I press "Finish"
      And I visit "john"
      And I should see <title>
      And I click <title>
     Then I should see <output>

  Examples:
    | title                  | url                                                 | output                   |
    | "Google"               | "http://maps.google.com"                            | "google maps"            |
    | "Obama"                | "LOCALHOST/obama/blog"                              | "Me and michelle obama"  |
    | "More publications"    | "LOCALHOST/john/publications"                       | "The Little Prince"      |
    | "Stocks"               | "http://finance.yahoo.com/q?s=AAPL&reco=1"          | "Apple"                  |
