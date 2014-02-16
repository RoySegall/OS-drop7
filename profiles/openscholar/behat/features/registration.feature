Feature:
  Testing the event registration module.

  @api @wip
  Scenario: Limit the registration capacity to 1 and verify it for a normal user.
    Given I am logging in as "john"
      And I turn on event registration on "Halley's Comet"
     When I visit "john/event/halleys-comet"
      And I set the event capacity to "1"
      And I fill in "Email" with "g@gmail.com"
      And I press "Signup"
     When I am logging in as "michelle"
      And I visit "john/event/halleys-comet"
      And I should not see "Sign up for Halley's Comet"
     Then I delete "john" registration

  @api @wip
  Scenario: Limit the registration capacity to 2 and verify it for a normal user.
    Given I am logging in as "john"
     When I visit "john/event/halleys-comet"
      And I set the event capacity to "2"
      And I fill in "Email" with "g@gmail.com"
      And I press "Signup"
     When I am logging in as "michelle"
      And I visit "john/event/halleys-comet"
      And I should see "Sign up for Halley's Comet"
     Then I delete "john" registration

  @api
  Scenario: Test adding event.
    Given I am logging in as "john"
      And I visit "john/node/add/event"
      And I fill in "Title" with "My New Event"
      And I check the box "Signup"
      And I press "Save"
     When I visit "john/calendar"
     Then I should see "My New Event"

  @api @wip
  Scenario: Test registering to event.
    Given I am logging in as "john"
      And I make "bill" a member in vsite "john"
      And I am logging in as "admin"
      And I make registration to event without javascript available
     When I am logging in as "bill"
      And I visit "john/event/my-new-event"
      And I fill in "Email" with "bill@example.com"
      And I fill in "Full name" with "Bill Clinton"
      And I fill in "Department" with "Astronomy"
      And I press "Signup"
     Then I am logging in as "john"
      And I visit "john/event/my-new-event"
      And I click "Manage Registrations"
      And I should see "bill@example.com"
      And I am logging in as "admin"
      And I make registration to event without javascript unavailable


