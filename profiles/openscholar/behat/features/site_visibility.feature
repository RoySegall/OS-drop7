Feature:
  Testing the visibility field.

  @api
  Scenario Outline: Define the site visibility field to "Anyone with the link"
                    and test that anonymous users can view the site.
     Given I visit <request-url>
      Then I should see <text>

  Examples:
    | request-url                     | text                                                |
    | "einstein"                      | "Einstein"                                          |
    | "einstein/blog"                 | "Mileva Marić"                                      |
    | "einstein/blog/mileva-marić"    | "Yesterday I met Mileva, what a nice girl :)."      |
