#!/usr/bin/env python3
"""Choose build validation and inventory maintenance independently."""
import argparse
import os


def lanes(reused, cache_hit, pull_request=False):
    if type(reused) is not bool or type(cache_hit) is not bool or type(pull_request) is not bool:
        raise ValueError('CI proof and cache decisions require booleans')
    # The host re-export of live receipts repeats the export step; main keeps it as a second check.
    return {'full': not reused, 'inventory': not reused or not cache_hit,
            'receipts': not reused and not pull_request}


def boolean(value):
    if value not in ('true', 'false'):
        raise argparse.ArgumentTypeError('Expected true or false')
    return value == 'true'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--reused', type=boolean, required=True)
    parser.add_argument('--cache-hit', type=boolean, required=True)
    parser.add_argument('--pull-request', type=boolean, required=True)
    args = parser.parse_args()
    with open(os.environ['GITHUB_OUTPUT'], 'a') as output:
        for name, enabled in lanes(args.reused, args.cache_hit, args.pull_request).items():
            output.write(f'{name}={str(enabled).lower()}\n')


if __name__ == '__main__':
    main()
