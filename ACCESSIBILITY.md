# Accessibility and inclusive contribution

**Language:** English (default) | [Français](ACCESSIBILITY.fr.md)

nanoDNS is a native background DNS payload, not a graphical application. Its public interfaces are the repository documentation, release downloads, installation instructions, diagnostic logs, and GitHub issue forms. We want people to be able to find, understand and use these resources regardless of their preferred language or accessibility needs.

## Documentation and release usability

- Documentation is written in plain text and Markdown, with descriptive headings and links instead of image-only instructions.
- Installation steps include copyable absolute file paths, explain how to replace the original Payload Manager autoload entry, and distinguish the console DNS settings from upstream Quad9 settings.
- English is the reference language. French equivalents are provided for important user-facing documents, and either language is welcome in reports.
- Console logs are text, but can expose hostnames and network information: redact them before sharing.

## What is and is not verified

We have **not conducted a formal accessibility audit** and do **not claim WCAG conformance**. The GitHub web interface and the third-party Payload Manager interface are outside this project's control. Firmware 13.60 has received one successful user hardware test for basic DNS operation and shutdown/power-on; other firmware and the secondary console build remain **not user-validated**. This hardware status is **not** an accessibility evaluation.

## Reporting barriers

Open a [documentation/accessibility issue](https://github.com/niakw/nanoDNS-13.60/issues/new/choose) and describe:

- The task that was difficult (for example, locating the correct download or following a migration step).
- The document heading or public URL, and what happened versus what you expected.
- Your environment or assistive technology **only if you wish to share it**; screenshots and recordings are optional.
- Any wording or alternative format that would make the task easier.

Do not include personal details, raw DNS logs or unredacted console identifiers in public reports. A maintainer can request a sanitized excerpt or clarify the instructions in the issue; no guaranteed response time is promised.

## Contributions

Prefer text equivalents for diagrams, meaningful link labels, simple heading order, descriptive code examples, and tested Markdown links. If changing user-facing instructions, update the corresponding English/French documents and say what you checked. See [contribution guidelines](CONTRIBUTING.md), [security guidance](SECURITY.md), and the [test plan](docs/TEST_PLAN.md).
